#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

// CORRECTED ADDRESSES based on your memory map
#define HPS_TO_FPGA_BASE    0xFF200000UL  // Base address for HPS-to-FPGA bridge
#define FIFO_0_IN_OFFSET    0x0004310cUL  // fifo_0.in actual address
#define FIFO_1_OUT_OFFSET   0x00043108UL  // fifo_1.out actual address

#define FIFO_0_BASE   (HPS_TO_FPGA_BASE + FIFO_0_IN_OFFSET)   // 0xFF20310c
#define FIFO_1_BASE   (HPS_TO_FPGA_BASE + FIFO_1_OUT_OFFSET)  // 0xFF203108

#define MAP_SIZE    0x50000  // Use hex for consistency

volatile uint32_t *fifo0_ptr;  // For sending audio data TO FPGA
volatile uint32_t *fifo1_ptr;  // For receiving control commands FROM FPGA

int paused = 0;
int current = 0;
int running = 1;
int song_changed = 0;

// Audio timing improvements
struct timespec start_time, current_time;
long samples_sent = 0;
#define SAMPLE_RATE 48000
#define NANOSECONDS_PER_SAMPLE (1000000000L / SAMPLE_RATE)  // ~20833 nanoseconds
#define CONTROL_CHECK_INTERVAL 480  // Check every 480 samples (~10ms at 48kHz)

void next_song() {
    current = (current + 1) % 3;
    song_changed = 1;
    printf("Switching to next song: %d\n", current);
}

void prev_song() {
    current = (current + 2) % 3;  // -1 with wrap around
    song_changed = 1;
    printf("Switching to previous song: %d\n", current);
}

void play_pause() {
    paused = !paused;
    printf("Playback %s\n", paused ? "PAUSED" : "RESUMED");
}

// Calculate expected time based on samples sent
long get_expected_time_ns() {
    return samples_sent * (long)NANOSECONDS_PER_SAMPLE;
}

// Get actual elapsed time in nanoseconds
long get_elapsed_time_ns() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec - start_time.tv_sec) * 1000000000L + (now.tv_nsec - start_time.tv_nsec);
}

// Improved timing function
void precise_audio_delay() {
    long expected_ns = get_expected_time_ns();
    long elapsed_ns = get_elapsed_time_ns();
    long delay_ns = expected_ns - elapsed_ns;

    if (delay_ns > 0 && delay_ns < 1000000) {  // Only delay if less than 1ms
        struct timespec delay_time;
        delay_time.tv_sec = 0;
        delay_time.tv_nsec = delay_ns;
        nanosleep(&delay_time, NULL);
    }
}

int main() {
    char* songs[3] = {
        "Kiss-I Was Made For Lovin You-1979.wav",
        "Haddaway-What is Love-1993.wav",
        "Alan Walker-Faded-2016.wav"
    };

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open /dev/mem");
        return -1;
    }

    // Map the FIFO region (need larger mapping for these addresses)
    void *map_base = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, HPS_TO_FPGA_BASE & ~(4096 - 1));
    if (map_base == MAP_FAILED) {
        perror("mmap HPS-to-FPGA bridge");
        close(fd);
        return -1;
    }

    // Calculate pointers for both FIFOs using actual addresses
    fifo0_ptr = (volatile uint32_t *) ((uint8_t*)map_base + FIFO_0_IN_OFFSET);   // fifo_0.in at 0x4310c
    fifo1_ptr = (volatile uint32_t *) ((uint8_t*)map_base + FIFO_1_OUT_OFFSET); // fifo_1.out at 0x43108

    printf("FIFO pointers initialized:\n");
    printf("fifo0_ptr (audio data TO FPGA): %p (0x%08lx)\n", fifo0_ptr, (unsigned long)FIFO_0_BASE);
    printf("fifo1_ptr (control FROM FPGA): %p (0x%08lx)\n", fifo1_ptr, (unsigned long)FIFO_1_BASE);

    // Initialize timing
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    while (running) {
        printf("Playing: %s\n", songs[current]);
        song_changed = 0;  // Reset song change flag

        FILE *fp = fopen(songs[current], "rb");
        if (!fp) {
            printf("Warning: Could not open %s, trying next song\n", songs[current]);
            next_song();
            continue;
        }

        // Skip WAV header (44 bytes for standard WAV)
        fseek(fp, 44, SEEK_SET);

        uint16_t sample;
        samples_sent = 0;

        // Reset timing for new song
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        // Control command checking variables
        int control_check_counter = 0;

        printf("Starting playback at %d Hz sample rate\n", SAMPLE_RATE);

        while (fread(&sample, sizeof(uint16_t), 1, fp) == 1 && !song_changed) {
            // Handle pause state
            while (paused && !song_changed) {
                usleep(10000);  // 10ms sleep while paused

                uint32_t control = *fifo1_ptr;
                if (control != 0) {
                    if (control == 0x8 || control == 0x4) {
                        play_pause();
                        *fifo1_ptr = 0;  // Clear the command
                    }
                    else if (control == 0x2) {
                        prev_song();
                        *fifo1_ptr = 0;  // Clear the command
                        break;  // Exit pause loop to change song
                    }
                    else if (control == 0x1) {
                        next_song();
                        *fifo1_ptr = 0;  // Clear the command
                        break;  // Exit pause loop to change song
                    }
                }
            }

            // If song was changed while paused, break out
            if (song_changed) break;

            // Check for control commands periodically (not every sample)
            if (control_check_counter++ >= CONTROL_CHECK_INTERVAL) {
                control_check_counter = 0;

                uint32_t control = *fifo1_ptr;

                if (control != 0) {
                    if (control == 0x8 || control == 0x4) {
                        play_pause();
                        *fifo1_ptr = 0;  // Clear the command after processing
                    }
                    else if (control == 0x2) {
                        prev_song();
                        *fifo1_ptr = 0;  // Clear the command
                        break;  // Break to change song
                    }
                    else if (control == 0x1) {
                        next_song();
                        *fifo1_ptr = 0;  // Clear the command
                        break;  // Break to change song
                    }
                }
            }

            // Send audio sample to FPGA
            *fifo0_ptr = (uint32_t)sample;
            samples_sent++;

            // Precise timing control
            precise_audio_delay();
        }

        fclose(fp);

        // If we finished the song naturally (not due to button press), advance to next song
        if (!song_changed && feof(fp)) {
            printf("Song finished naturally, advancing to next song\n");
            next_song();
        }

        // Small delay between songs
        usleep(100000);  // 100ms
    }

    printf("Shutting down audio player\n");
    munmap(map_base, MAP_SIZE);
    close(fd);
    return 0;
}
