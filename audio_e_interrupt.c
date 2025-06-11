#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdbool.h>

// Variables timer
#define SEG2  SEG1_BASE  // Seconds units
#define SEG1  SEG2_BASE  // Seconds tens
#define MIN2  MIN1_BASE  // Minutes units
#define MIN1  MIN2_BASE  // Minutes tens
#define PAUSE_SW_BASE  PAUSA_BASE  // Address of the pause switch
#define ANTERIOR  ANTERIOR_BASE
#define SIGUIENTE  SIGUIENTE_BASE
#define TIMER   TIMER_BASE
unsigned int elapsed_ms;
void timer_ir_handler (void * context);
volatile bool paused = false;


//Variables sonido
#define AUDIO_0_BASE          AUDIO_BASE
#define AUDIO_CONTROL       (AUDIO_0_BASE + 0x0)
#define AUDIO_FIFOSPACE     (AUDIO_0_BASE + 0x4)
#define AUDIO_LEFT_DATA     (AUDIO_0_BASE + 0x8)
#define AUDIO_RIGHT_DATA    (AUDIO_0_BASE + 0xC)
#define AMPLITUDE   10000
#define SAMPLE_RATE 48000
volatile unsigned int *audio_control_ptr = (unsigned int *) AUDIO_CONTROL;
volatile unsigned int *audio_fifospace_ptr = (unsigned int *) AUDIO_FIFOSPACE;
volatile unsigned int *audio_left_ptr = (unsigned int *) AUDIO_LEFT_DATA;
volatile unsigned int *audio_right_ptr = (unsigned int *) AUDIO_RIGHT_DATA;

//Funciones timer
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

    *(volatile int*) SEG2 = decoder7seg(sec % 10);
    *(volatile int*) SEG1 = decoder7seg(sec / 10);
    *(volatile int*) MIN2 = decoder7seg(min % 10);
    *(volatile int*) MIN1 = decoder7seg(min / 10);
}

void timer_ir_handler(void * context) {
    volatile int* timer_status_ptr = (int*) TIMER;
    *timer_status_ptr = 0;           // clear interrupt

    // --- lógica de pausa (igual que antes) ---
    unsigned int sw = *(volatile unsigned int*) PAUSE_SW_BASE;
    bool new_paused = (sw & 0x1) != 0;
    static bool last_paused = false;
    if (new_paused && !last_paused)      *audio_control_ptr = 0x8;
    else if (!new_paused && last_paused) *audio_control_ptr = 0x0;
    last_paused = new_paused;
    paused = new_paused;
    // ------------------------------------------

    if (!paused) {
        elapsed_ms++;                     // contar segundos
        update_display(elapsed_ms);       // actualizar 7-seg aquí
    }
}


//Funciones audio
void init_audio() {
    *audio_control_ptr = 0x8;
    *audio_control_ptr = 0x0;
    alt_printf("Audio inicializado\n");
}

int get_fifo_space() {
    return (*audio_fifospace_ptr >> 24) & 0xFF;
}

void write_audio_sample(int sample) {
    while (get_fifo_space() == 0);
    unsigned int s = (unsigned int)(sample & 0xFFFFFF);
    *audio_left_ptr  = s;
    *audio_right_ptr = s;
}



int main() {
    if (*(volatile unsigned int*)TIMER != 0) return 1;
    alt_irq_register(TIMER_IRQ, NULL, timer_ir_handler);

    volatile unsigned int *ctr    = ((unsigned int*)TIMER) + 1;
    volatile unsigned int *status = (unsigned int*)TIMER;
    *ctr    = 0x7;
    while (*status != 0x2);

    elapsed_ms = 0;
    init_audio();

    int phase = 0;
    const int AMPL = AMPLITUDE;
    for (;;) {
        if (!paused) {
            int sample;
            if (phase < AMPL/2)             sample = phase * 4;
            else if (phase < AMPL)          sample = AMPL*2 - (phase * 4);
            else if (phase < AMPL*3/2)      sample = -(phase - AMPL) * 4;
            else                             sample = -(AMPL*2 - (phase - AMPL)*4);

            phase += 200;
            if (phase >= AMPL*2) phase = 0;
            write_audio_sample(sample);
        } else {
            for (volatile int i = 0; i < 1000; i++);
        }
    }
    return 0;
}
