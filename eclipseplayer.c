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
#define EQ1 FILT1_BASE
#define EQ2 FILT2_BASE
#define EQ3 FILT3_BASE
#define EQ4 FILT4_BASE

// FIFO Communication with microSD program
#define FIFO_IN_BASE   0x0004310C  // Audio data FROM microSD
#define FIFO_OUT_BASE  0x00043108  // Control commands TO microSD
#define FIFO_STATUS_BASE 0x00043110  // Add status register if available

#define TIMER   TIMER_BASE
unsigned int elapsed_ms;
void timer_ir_handler (void * context);
volatile bool paused = false;
volatile bool eq1 = false;
volatile bool eq2 = false;
volatile bool eq3 = false;
volatile bool eq4 = false;
volatile unsigned int *fifo_in_ptr = (unsigned int *) FIFO_IN_BASE;
volatile unsigned int *fifo_out_ptr = (unsigned int *) FIFO_OUT_BASE;

// Add previous button states to prevent continuous sending
static bool last_btn_prev = false;
static bool last_btn_next = false;

// Add audio sample buffer for smoother playback
#define AUDIO_BUFFER_SIZE 1024
static int audio_buffer[AUDIO_BUFFER_SIZE];
static int buffer_read_idx = 0;
static int buffer_write_idx = 0;
static int buffer_count = 0;

//Variables VGA -------------------------------------------------------------------------
#define FPGA_CHAR_BASE      VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE
#define CHAR_BUF_CTRL_BASE  VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE
#define MSG_RAM_BASE        RAM_BASE
#define VGA_COLS            80
#define VGA_ROWS            30
#define MSG_BUF_ADDR 0x20000u
#define MAX(a,b)  ( ((a) > (b)) ? (a) : (b) )

#define ORDER 8

float b1[9] = {
    0.0048f, 0.0f, -0.0192f, 0.0f, 0.0288f,
    0.0f, -0.0192f, 0.0f, 0.0048f
};

float a1[9] = {
    1.0f, -5.708f, 14.451f, -23.090f, 24.964f,
    -17.711f, 8.062f, -2.092f, 0.250f
};

float b2[9] = {
    0.0143f, 0.0f, -0.0571f, 0.0f, 0.0856f,
    0.0f, -0.0571f, 0.0f, 0.0143f
};

float a2[9] = {
    1.0f, -3.785f, 8.232f, -11.006f, 10.300f,
    -6.435f, 2.538f, -0.601f, 0.055f
};

float b3[9] = {
    0.0143f, 0.0f, -0.0571f, 0.0f, 0.0856f,
    0.0f, -0.0571f, 0.0f, 0.0143f
};

float a3[9] = {
    1.0f, -2.163f, 4.020f, -4.922f, 4.387f,
    -2.494f, 0.886f, -0.182f, 0.017f
};

float b4[9] = {
    0.0048f, 0.0f, -0.0192f, 0.0f, 0.0288f,
    0.0f, -0.0192f, 0.0f, 0.0048f
};

float a4[9] = {
    1.0f, -0.372f, 1.129f, -1.621f, 1.509f,
    -0.877f, 0.311f, -0.061f, 0.006f
};

// History buffers for input and output (using float for speed)
float x_hist_1[ORDER + 1] = {0};
float y_hist_1[ORDER + 1] = {0};
float x_hist_2[ORDER + 1] = {0};
float y_hist_2[ORDER + 1] = {0};
float x_hist_3[ORDER + 1] = {0};
float y_hist_3[ORDER + 1] = {0};
float x_hist_4[ORDER + 1] = {0};
float y_hist_4[ORDER + 1] = {0};

float apply_filter(float x_new, const float* b, const float* a, float* x_hist, float* y_hist) {
    // Shift history arrays
    for (int i = ORDER; i > 0; i--) {
        x_hist[i] = x_hist[i - 1];
        y_hist[i] = y_hist[i - 1];
    }
    x_hist[0] = x_new;

    float y_new = 0;
    for (int i = 0; i <= ORDER; i++) {
        y_new += b[i] * x_hist[i];
        if (i > 0)
            y_new -= a[i] * y_hist[i - 1];
    }

    y_hist[0] = y_new;
    return y_new;
}

#define NUM_SONGS 3
const char *song_msgs[NUM_SONGS] = {
    "Pokemon Blue/Red- Lavender Town",
    "Ghost Fight",
    "Champion Cynthia Battle Music"
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

    unsigned int sweq1 = *(volatile unsigned int*)EQ1;
    bool new_filt1 = (sweq1 & 1) != 0;

    unsigned int sweq2 = *(volatile unsigned int*)EQ2;
    bool new_filt2 = (sweq2 & 1) != 0;

    unsigned int sweq3 = *(volatile unsigned int*)EQ3;
    bool new_filt3 = (sweq3 & 1) != 0;

    unsigned int sweq4 = *(volatile unsigned int*)EQ4;
    bool new_filt4 = (sweq4 & 1) != 0;

    static bool last_paused = false;

    // Send pause/play command to microSD program ONLY ON EDGE
    if (new_paused && !last_paused) {
        *fifo_out_ptr = 0x8;  // Send pause command
        *(volatile unsigned int*)AUDIO_CONTROL = 0x8;
    } else if (!new_paused && last_paused) {
        *fifo_out_ptr = 0x4;  // Send play command
        *(volatile unsigned int*)AUDIO_CONTROL = 0x0;
    }

    last_paused = new_paused;
    paused = new_paused;

    eq1 = new_filt1;
    eq2 = new_filt2;
    eq3 = new_filt3;
    eq4 = new_filt4;

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

// Improved FIFO reading with basic flow control
int read_audio_from_fifo() {
    static int last_sample = 0;
    static unsigned int sample_counter = 0;

    // Read new sample from FIFO
    int new_sample = (int)*fifo_in_ptr;

    // Basic validation - if sample is exactly the same as last few samples,
    // it might be stale data
    if (new_sample != last_sample || (sample_counter % 100) == 0) {
        last_sample = new_sample;
        sample_counter++;
        return new_sample;
    }

    sample_counter++;
    return last_sample; // Return last valid sample if current seems stale
}

// Buffer management functions
void add_to_buffer(int sample) {
    if (buffer_count < AUDIO_BUFFER_SIZE) {
        audio_buffer[buffer_write_idx] = sample;
        buffer_write_idx = (buffer_write_idx + 1) % AUDIO_BUFFER_SIZE;
        buffer_count++;
    }
}

int get_from_buffer() {
    if (buffer_count > 0) {
        int sample = audio_buffer[buffer_read_idx];
        buffer_read_idx = (buffer_read_idx + 1) % AUDIO_BUFFER_SIZE;
        buffer_count--;
        return sample;
    }
    return 0; // Return silence if buffer is empty
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
    // --- Timer 1ms + ISR 7-seg ---
    if (*(volatile unsigned int*)TIMER) return 1;
    alt_irq_register(TIMER_IRQ, NULL, timer_ir_handler);
    *(volatile unsigned int*)(TIMER + 4) = (TIMER_FREQ/1000) - 1;  // 1ms timer
    *(volatile unsigned int*)TIMER       = 0x7;
    while (*(volatile unsigned int*)TIMER != 0x2);
    elapsed_ms = 0;
    int song_index = 0;

    init_audio();
    init_message_ram(song_msgs[song_index]);
    vga_show_from_ram();

    volatile unsigned int *btn_prev = (unsigned int*)ANTERIOR;
    volatile unsigned int *btn_next = (unsigned int*)SIGUIENTE;

    // Audio processing timing variables
    unsigned int audio_counter = 0;
    const unsigned int AUDIO_PROCESS_INTERVAL = 1; // Process audio every 1ms (1000Hz)

    // Control checking variables
    unsigned int control_counter = 0;
    const unsigned int CONTROL_CHECK_INTERVAL = 10; // Check controls every 10ms

    alt_printf("Audio player initialized, starting main loop\n");

    for (;;) {
        // Handle control buttons every 10ms
        if (control_counter++ >= CONTROL_CHECK_INTERVAL) {
            control_counter = 0;

            bool prev_now = (*btn_prev & 1) == 0;
            bool next_now = (*btn_next & 1) == 0;

            // Handle previous song button - ONLY ON FALLING EDGE
            if (prev_now && !last_btn_prev) {
                *fifo_out_ptr = 0x2;  // Send previous song command to microSD
                song_index = (song_index + NUM_SONGS - 1) % NUM_SONGS; // Wrap around properly
                elapsed_ms = 0;
                update_display(elapsed_ms);
                *audio_control_ptr = 0x8;
                *audio_control_ptr = 0x0;
                init_message_ram(song_msgs[song_index]);
                vga_show_from_ram();
                alt_printf("Previous song: %s\n", song_msgs[song_index]);

                // Clear audio buffer on song change
                buffer_read_idx = buffer_write_idx = buffer_count = 0;
            }
            last_btn_prev = prev_now;

            // Handle next song button - ONLY ON FALLING EDGE
            if (next_now && !last_btn_next) {
                *fifo_out_ptr = 0x1;  // Send next song command to microSD
                song_index = (song_index + 1) % NUM_SONGS; // Wrap around properly
                elapsed_ms = 0;
                update_display(elapsed_ms);
                *audio_control_ptr = 0x8;
                *audio_control_ptr = 0x0;
                init_message_ram(song_msgs[song_index]);
                vga_show_from_ram();
                alt_printf("Next song: %s\n", song_msgs[song_index]);

                // Clear audio buffer on song change
                buffer_read_idx = buffer_write_idx = buffer_count = 0;
            }
            last_btn_next = next_now;
        }

        if (!paused) {
            // Process audio at a controlled rate
            if (audio_counter++ >= AUDIO_PROCESS_INTERVAL) {
                audio_counter = 0;

                // READ AUDIO SAMPLE FROM FIFO
                int sample = read_audio_from_fifo();

                // Add to buffer for smoother playback
                add_to_buffer(sample);

                // Process samples from buffer
                if (buffer_count > 10) { // Only process when we have some buffered samples
                    int buffered_sample = get_from_buffer();

                    // Apply equalizer filters if enabled (optimized)
                    float processed_sample = (float)buffered_sample;

                    // Apply filters only if they're enabled (saves computation)
                    if (eq1) {
                        processed_sample = apply_filter(processed_sample, b1, a1, x_hist_1, y_hist_1);
                    }
                    if (eq2) {
                        processed_sample = apply_filter(processed_sample, b2, a2, x_hist_2, y_hist_2);
                    }
                    if (eq3) {
                        processed_sample = apply_filter(processed_sample, b3, a3, x_hist_3, y_hist_3);
                    }
                    if (eq4) {
                        processed_sample = apply_filter(processed_sample, b4, a4, x_hist_4, y_hist_4);
                    }

                    // Output the processed audio sample
                    write_audio_sample((int)processed_sample);
                }
            }
        } else {
            // When paused, still read from FIFO to prevent overflow but don't output
            read_audio_from_fifo();
            for (volatile int i = 0; i < 1000; i++); // Small delay
        }

        // Small delay to prevent overwhelming the system
        for (volatile int i = 0; i < 100; i++);
    }

    return 0;
}
