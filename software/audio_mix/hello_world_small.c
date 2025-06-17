#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>    // usleep

// --- Shared memory para audio desde HPS ---
#define SHARED_MEM_BASE  0x00000000      // Igual que en tu primer código
#define BUFFER_OFFSET    0x10
#define BUFFER_SIZE      128             // Número de bytes (cada muestra ocupa 2 bytes)
#define FLAG_OFFSET      0x00
volatile uint32_t shared_mem = (volatile uint32_t) SHARED_MEM_BASE;

// --- Variables timer + display 7-seg ---
#define SEG2       SEG1_BASE  // Seconds units
#define SEG1       SEG2_BASE  // Seconds tens
#define MIN2       MIN1_BASE  // Minutes units
#define MIN1       MIN2_BASE  // Minutes tens
#define PAUSE_SW   PAUSA_BASE // Switch de pausa
#define TIMER      TIMER_BASE
#define TIMER_IRQ  TIMER_IRQ_INTERRUPT_CONTROLLER_ID
extern const int TIMER_FREQ;  // Definido por sistema

unsigned int elapsed_ms = 0;
volatile bool paused = false;

int decoder7seg(int number) {
    switch (number) {
        case 0: return ~0b00111111;
        case 1: return ~0b00000110;
        case 2: return ~0b01011011;
        case 3: return ~0b01001111;
        case 4: return ~0b01100110;
        case 5: return ~0b01101101;
        case 6: return ~0b01111101;
        case 7: return ~0b00000111;
        case 8: return ~0b01111111;
        case 9: return ~0b01101111;
        default: return ~0b00000000;
    }
}

void update_display(unsigned int seconds) {
    unsigned int min = (seconds / 60) % 60;
    unsigned int sec = seconds % 60;
    (volatile int) SEG2 = decoder7seg(sec % 10);
    (volatile int) SEG1 = decoder7seg(sec / 10);
    (volatile int) MIN2 = decoder7seg(min % 10);
    (volatile int) MIN1 = decoder7seg(min / 10);
}

void timer_ir_handler(void *context) {
    // Acknowledge timer
    (volatile int)(TIMER) = 0;
    // Leer switch de pausa
    bool new_paused = ((volatile unsigned int)PAUSE_SW & 1) != 0;
    static bool last_paused = false;
    // Silenciar/unmute hardware de audio
    if (new_paused && !last_paused)      (volatile unsigned int)(AUDIO_0_BASE + 0x0) = 0x8;
    else if (!new_paused && last_paused) (volatile unsigned int)(AUDIO_0_BASE + 0x0) = 0x0;
    last_paused = new_paused;
    paused = new_paused;

    if (!paused) {
        elapsed_ms++;
        update_display(elapsed_ms);
    }
}

// --- VGA textado ---
#define VGA_CHAR_BASE      VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE
#define CHAR_BUF_CTRL_BASE VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE
#define MSG_BUF_ADDR       RAM_BASE
#define VGA_COLS           80
#define VGA_ROWS           30

void init_message_ram(const char *text) {
    volatile char msg_ram = (volatile char)MSG_BUF_ADDR;
    size_t len = strlen(text) + 1;
    for (size_t i = 0; i < len; ++i) msg_ram[i] = text[i];
}

void vga_show_from_ram(void) {
    volatile const char msg = (volatile const char)MSG_BUF_ADDR;
    volatile uint32_t ctrl  = (volatile uint32_t)CHAR_BUF_CTRL_BASE;
    volatile uint16_t buf   = (volatile uint16_t)VGA_CHAR_BASE;
    // limpiar pantalla
    ctrl[1] = VGA_CHAR_BASE;
    for (int i = 0; i < VGA_COLS*VGA_ROWS; ++i) buf[i] = ' ';
    // centrar primera línea
    int len = 0;
    while (msg[len] && msg[len] != '\n') ++len;
    int row = VGA_ROWS/2;
    int col = (VGA_COLS - len)/2;
    if (col < 0) col = 0;
    int idx = row * VGA_COLS + col;
    for (int i = 0; i < len; ++i) buf[idx + i] = msg[i];
    ctrl[0] = 1;
}

// --- Control de FIFO de audio ---
#define AUDIO_CONTROL     (AUDIO_BASE + 0x0)
#define AUDIO_FIFOSPACE   (AUDIO_BASE + 0x4)
#define AUDIO_LEFT_DATA   (AUDIO_BASE + 0x8)
#define AUDIO_RIGHT_DATA  (AUDIO_BASE + 0xC)

static inline int get_fifo_space() {
    return ((volatile unsigned int)AUDIO_FIFOSPACE >> 24) & 0xFF;
}

static inline void write_audio_sample(int16_t sample) {
    // Esperar espacio en FIFO
    while (get_fifo_space() == 0);
    unsigned int s = (unsigned int)(sample & 0xFFFF);
    (volatile unsigned int)AUDIO_LEFT_DATA  = s;
    (volatile unsigned int)AUDIO_RIGHT_DATA = s;
}

int main(void) {
    // --- Inicializar timer + ISR ---
    if ((volatile unsigned int)TIMER) return 1;
    alt_irq_register(TIMER_IRQ, NULL, timer_ir_handler);
    (volatile unsigned int)(TIMER + 4) = (TIMER_FREQ/1) - 1;
    (volatile unsigned int)TIMER       = 0x7;
    while ((volatile unsigned int)TIMER != 0x2);
    elapsed_ms = 0;

    // --- Mostrar primera canción y timer ---
    init_message_ram("Reproduciendo audio desde HPS...");
    vga_show_from_ram();

    // Banderas para botones de cambio de canción (no se usan aquí)
    volatile unsigned int btn_prev = (unsigned int)ANTERIOR;
    volatile unsigned int btn_next = (unsigned int)SIGUIENTE;

    for (;;) {
        // --- Manejo de reproducción desde memoria compartida ---
        if (!paused && shared_mem[FLAG_OFFSET] == 1) {
            // Hay un bloque de BUFFER_SIZE bytes (LSB/MSB) listo
            for (int i = 0; i < BUFFER_SIZE; i += 2) {
                uint8_t lsb = ((volatile uint8_t)SHARED_MEM_BASE + BUFFER_OFFSET + i);
                uint8_t msb = ((volatile uint8_t)SHARED_MEM_BASE + BUFFER_OFFSET + i + 1);
                int16_t sample = (msb << 8) | lsb;
                write_audio_sample(sample);
            }
            // Limpiar flag para HPS
            shared_mem[FLAG_OFFSET] = 0;
        }
        // Si está en pausa, simplemente dejamos CPU ocupada ligeramente
        else if (paused) {
            for (volatile int i = 0; i < 1000; i++);
        }
        // Opcional: aquí podrías atender botones prev/next si quisieras cambiar fuente
    }

    return 0;
}
