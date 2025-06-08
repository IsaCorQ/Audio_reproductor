/*
 * Generador de audio simplificado usando punteros directos
 * Compatible con CPUlator - acceso directo a memoria
 */

#include <stdio.h>
#include "system.h"
// Direcciones base de los periféricos (ajustar según tu sistema)
#define AUDIO_0_BASE          AUDIO_BASE
#define AUDIO_CONTROL       (AUDIO_0_BASE + 0x0)
#define AUDIO_FIFOSPACE     (AUDIO_0_BASE + 0x4)
#define AUDIO_LEFT_DATA     (AUDIO_0_BASE + 0x8)
#define AUDIO_RIGHT_DATA    (AUDIO_0_BASE + 0xC)

#define AMPLITUDE   10000
#define SAMPLE_RATE 48000

// Punteros para acceso directo a registros
volatile unsigned int *audio_control_ptr = (unsigned int *) AUDIO_CONTROL;
volatile unsigned int *audio_fifospace_ptr = (unsigned int *) AUDIO_FIFOSPACE;
volatile unsigned int *audio_left_ptr = (unsigned int *) AUDIO_LEFT_DATA;
volatile unsigned int *audio_right_ptr = (unsigned int *) AUDIO_RIGHT_DATA;

void init_audio() {
    // Reset del controlador de audio
    *audio_control_ptr = 0x8;  // Clear FIFOs
    *audio_control_ptr = 0x0;  // Normal operation
    printf("Audio inicializado\n");
}

int get_fifo_space() {
    // Retorna el espacio disponible en el FIFO izquierdo
    return (*audio_fifospace_ptr >> 24) & 0xFF;
}

void write_audio_sample(int sample) {
    // Esperar hasta que haya espacio en el FIFO
    while (get_fifo_space() == 0) {
        // Esperar
    }

    // Convertir muestra a formato unsigned de 24 bits
    unsigned int audio_sample = (unsigned int)(sample & 0xFFFFFF);

    // Escribir a ambos canales
    *audio_left_ptr = audio_sample;
    *audio_right_ptr = audio_sample;
}

int main() {
    int phase = 0;
    int sample;

    printf("Iniciando generador de audio...\n");

    // Inicializar audio
    init_audio();

    while (1) {
        // Generar onda triangular
        if (phase < AMPLITUDE/2) {
            sample = phase * 4;
        } else if (phase < AMPLITUDE) {
            sample = AMPLITUDE*2 - (phase * 4);
        } else if (phase < AMPLITUDE*3/2) {
            sample = -(phase - AMPLITUDE) * 4;
        } else {
            sample = -(AMPLITUDE*2 - (phase - AMPLITUDE) * 4);
        }

        // Incrementar fase
        phase += 200;
        if (phase >= AMPLITUDE*2) {
            phase = 0;
        }

        // Escribir muestra al audio
        write_audio_sample(sample);
    }

    return 0;
}
