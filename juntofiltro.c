#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// Variables timer -------------------------------------------------------------------------
#define SEG2  SEG1_BASE  // Seconds units
#define SEG1  SEG2_BASE  // Seconds tens
#define MIN2  MIN1_BASE  // Minutes units
#define MIN1  MIN2_BASE  // Minutes tens
#define PAUSE_SW_BASE  PAUSA_BASE  // Address of the pause switch
#define ANTERIOR  SIGUIENTE_BASE
#define SIGUIENTE  ANTERIOR_BASE
#define LOWPASS FILT1_BASE
#define HIGHPASS FILT2_BASE
#define TIMER   TIMER_BASE
unsigned int elapsed_ms;
void timer_ir_handler (void * context);
volatile bool paused = false;
volatile bool lowpass = false;
volatile bool highpass = false;

//Variables VGA -------------------------------------------------------------------------
#define FPGA_CHAR_BASE      VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE
#define CHAR_BUF_CTRL_BASE  VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE
#define MSG_RAM_BASE        RAM_BASE
#define VGA_COLS            80
#define VGA_ROWS            30
#define MSG_BUF_ADDR 0x20000u
#define MAX(a,b)  ( ((a) > (b)) ? (a) : (b) )

#define FILTER_ORDER 2
float b_lp[3] = {0.0675f, 0.1349f, 0.0675f};
float a_lp[3] = {1.0000f, -1.1430f, 0.4128f};

float b_hp[3] = {0.8006, -1.6013, 0.8006};
float a_hp[3] = {1.0000, -1.5610, 0.6414};

// Buffers for filter history
float x_hist[FILTER_ORDER + 1] = {0};
float y_hist[FILTER_ORDER + 1] = {0};

float apply_lowpass(float new_x) {
    // Shift history
    for (int i = FILTER_ORDER; i > 0; i--) {
        x_hist[i] = x_hist[i - 1];
        y_hist[i] = y_hist[i - 1];
    }
    x_hist[0] = new_x;

    // Apply difference equation
    float y_new = 0.0f;
    for (int i = 0; i <= FILTER_ORDER; i++)
        y_new += b_lp[i] * x_hist[i];
    for (int i = 1; i <= FILTER_ORDER; i++)
        y_new -= a_lp[i] * y_hist[i];

    y_hist[0] = y_new;
    return y_new;
}

float apply_highpass(float new_x) {
    // Shift history
    for (int i = FILTER_ORDER; i > 0; i--) {
        x_hist[i] = x_hist[i - 1];
        y_hist[i] = y_hist[i - 1];
    }
    x_hist[0] = new_x;

    // Apply high-pass difference equation
    float y_new = 0.0f;
    for (int i = 0; i <= FILTER_ORDER; i++)
        y_new += b_hp[i] * x_hist[i];
    for (int i = 1; i <= FILTER_ORDER; i++)
        y_new -= a_hp[i] * y_hist[i];

    y_hist[0] = y_new;
    return y_new;
}

#define NUM_SONGS 3
const char *song_msgs[NUM_SONGS] = {
    "Hardwired de Metallica",
    "The Nights de Avicii",
    "BYOB de System of a Down"
};


//Variables sonido -------------------------------------------------------------------------
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

//Funciones timer -------------------------------------------------------------------------
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

void timer_ir_handler(void *context) {
    volatile int *stat = (int*)TIMER;
    *stat = 0;
    unsigned int sw = *(volatile unsigned int*)PAUSE_SW_BASE;
    bool new_paused = (sw & 1) != 0;
    unsigned int swfilt = *(volatile unsigned int*)LOWPASS;
    bool new_filt = (swfilt & 1) != 0;
    unsigned int swfilt2 = *(volatile unsigned int*)HIGHPASS;
    bool new_filt2 = (swfilt2 & 1) != 0;
    static bool last_paused = false;
    if (new_paused && !last_paused)      * (volatile unsigned int*)AUDIO_CONTROL = 0x8;
    else if (!new_paused && last_paused) * (volatile unsigned int*)AUDIO_CONTROL = 0x0;
    last_paused = new_paused;
    paused = new_paused;
    lowpass = new_filt;
    highpass = new_filt2;

    if (!paused) {
        elapsed_ms++;
        update_display(elapsed_ms);
    }
}


//Funciones audio -------------------------------------------------------------------------
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





//Funciones VGA -------------------------------------------------------------------------
void init_message_ram(const char *text) {
    volatile char *msg_ram = (volatile char*)MSG_BUF_ADDR;
    size_t len = strlen(text) + 1;
    for (size_t i = 0; i < len; ++i)
        msg_ram[i] = text[i];
}

void vga_show_from_ram(void) {
    volatile const char *msg = (volatile const char*)MSG_BUF_ADDR;
    volatile uint32_t *ctrl  = (volatile uint32_t*)CHAR_BUF_CTRL_BASE;
    volatile uint16_t *buf   = (volatile uint16_t*)FPGA_CHAR_BASE;

    ctrl[1] = FPGA_CHAR_BASE;
    for (int i = 0; i < VGA_COLS*VGA_ROWS; ++i) {
        buf[i] = ' ';
    }
    int len = 0;
    while (msg[len] && msg[len] != '\n') {
        ++len;
    }
    int row = VGA_ROWS/2;
    int col = (VGA_COLS - len) / 2;
    if (col < 0) col = 0;
    int idx = row * VGA_COLS + col;
    for (int i = 0; i < len; ++i) {
        buf[idx + i] = msg[i];
    }
    ctrl[0] = 1;
}



int main(void) {
    // --- Timer 1s + ISR 7-seg ---
    if (*(volatile unsigned int*)TIMER) return 1;
    alt_irq_register(TIMER_IRQ, NULL, timer_ir_handler);
    *(volatile unsigned int*)(TIMER + 4) = (TIMER_FREQ/1) - 1;
    *(volatile unsigned int*)TIMER       = 0x7;
    while (*(volatile unsigned int*)TIMER != 0x2);
    elapsed_ms = 0;
    int song_index = 0;


    init_audio();
    init_message_ram(song_msgs[song_index]);
    vga_show_from_ram();

    volatile unsigned int *btn_prev = (unsigned int*)ANTERIOR;
    volatile unsigned int *btn_next = (unsigned int*)SIGUIENTE;

    int phase = 0;
    const int PHASE_INC = 200;
    const int PERIOD    = AMPLITUDE*2;

    bool prev_last = false;
    bool next_last = false;

    for (;;) {
        bool prev_now = (*btn_prev & 1) != 0;
        bool next_now = (*btn_next & 1) != 0;

        if (prev_now && !prev_last) {
            if (song_index > 0) {
                song_index--;
                phase      = 0;
                elapsed_ms = 0;
                update_display(elapsed_ms);
                *audio_control_ptr = 0x8;
                *audio_control_ptr = 0x0;
                init_message_ram(song_msgs[song_index]);
                vga_show_from_ram();
            }
        }
        prev_last = prev_now;

        if (next_now && !next_last) {
            if (song_index < NUM_SONGS - 1) {
                song_index++;
                phase      = 0;
                elapsed_ms = 0;
                update_display(elapsed_ms);
                // reinicia audio
                *audio_control_ptr = 0x8;
                *audio_control_ptr = 0x0;
                init_message_ram(song_msgs[song_index]);
                vga_show_from_ram();
            }
        }
        next_last = next_now;

        if (!paused) {
            int sample;
            switch (song_index) {
                case 0: // sawtooth
                    sample = (phase % PERIOD) - AMPLITUDE;
                    break;
                case 1: // triangle
                    sample = (phase < AMPLITUDE)
                    ?  phase
                    : (PERIOD - phase);
                    break;
                case 2: // square
                default:
                    sample = (phase < AMPLITUDE)
                    ?  AMPLITUDE
                    : -AMPLITUDE;
                    break;
            }
            phase += PHASE_INC;
            if (phase >= PERIOD) phase -= PERIOD;
            if (lowpass){
                float filtered = apply_lowpass((float)sample);
                write_audio_sample((int)filtered);
            }
            if (highpass){
                float filtered = apply_highpass((float)sample);
                write_audio_sample((int)filtered);
            }
            write_audio_sample(sample);
        } else {
            for (volatile int i = 0; i < 1000; i++);
        }
    }

    return 0;
}
