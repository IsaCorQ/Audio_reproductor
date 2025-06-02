/*
 * Ejemplo basico de reproductor con tres ondas, control por botones y display de tiempo
 *
 * Requisitos en Platform Designer:
 *   - IP "Audio Clock for DE-series Boards" conectado a audio_0.clk
 *   - IP "Audio" (altera_up_avalon_audio) configurado a 24 bits (Audio Out habilitado)
 *   - IP "Audio and Video Config" en modo I2S a 24 bits, 48 kHz y "Auto Initialize"
 *   - PIO para boton NEXT   (SIGUIENTE_BASE)
 *   - PIO para boton PREV   (ANTERIOR_BASE)
 *   - PIO para switch PAUSE (PAUSA_BASE)
 *   - PIO de salida para cuatro displays de 7 segmentos (anodo comun):
 *       SEG1_BASE, SEG2_BASE, MIN1_BASE, MIN2_BASE
 *
 * Este codigo genera:
 *   - Onda 0: sierra
 *   - Onda 1: cuadrada
 *   - Onda 2: triangular
 *
 * Controles:
 *   - Boton NEXT  para avanzar a la proxima onda
 *   - Boton PREV  para retroceder a la onda anterior
 *   - Switch PAUSE para pausar o reanudar la reproduccion
 *
 * El tiempo transcurrido (minutos:segundos) se muestra en los displays.
 */

#include "system.h"
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "unistd.h"   // para usleep()

#define NEXT_BTN_BASE        SIGUIENTE_BASE
#define PREV_BTN_BASE        ANTERIOR_BASE
#define SWITCH_PAUSE_BASE    PAUSA_BASE

#define SEVENSEG_SEG1_BASE   SEG1_BASE
#define SEVENSEG_SEG2_BASE   SEG2_BASE
#define SEVENSEG_MIN1_BASE   MIN1_BASE
#define SEVENSEG_MIN2_BASE   MIN2_BASE

#define AMPLITUDE   30000
#define SAMPLE_RATE 48000

/* Tabla 7 segmentos (anodo comun), bits [6:0]= segmentos A-G, bit 7= punto apagado */
static const unsigned char seven_seg_digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

int main()
{
    alt_up_audio_dev * audio_dev;
    int phase;
    int wave_type = 0;       /* 0= sierra, 1= cuadrada, 2= triangular */
    int sample_count = 0;    /* conteo de muestras reproducidas */
    unsigned int sample_buf[1];
    int btn_next, btn_prev;
    int prev_btn_next = 0;
    int prev_btn_prev = 0;
    int paused = 0;
    int switch_pause;

    /* Abrir dispositivo de audio */
    audio_dev = alt_up_audio_open_dev("/dev/audio_0");
    if (audio_dev == NULL) {
        alt_printf("Error: no se encontro /dev/audio_0\n");
        return -1;
    }
    alt_printf("Audio_0 abierto.\n");

    /* Resetear audio core para inicializar el CODEC WM8731 */
    alt_up_audio_reset_audio_core(audio_dev);
    alt_printf("Audio core reiniciado.\n");

    /* Inicializar fase en valor minimo */
    phase = -AMPLITUDE;

    while (1)
    {
        /* Leer boton NEXT (detecta flanco de subida) */
        btn_next = IORD_ALTERA_AVALON_PIO_DATA(NEXT_BTN_BASE) & 0x1;
        if (btn_next && !prev_btn_next) {
            wave_type = (wave_type + 1) % 3;
        }
        prev_btn_next = btn_next;

        /* Leer boton PREV (detecta flanco de subida) */
        btn_prev = IORD_ALTERA_AVALON_PIO_DATA(PREV_BTN_BASE) & 0x1;
        if (btn_prev && !prev_btn_prev) {
            wave_type = (wave_type + 2) % 3; /* equivale a -1 mod 3 */
        }
        prev_btn_prev = btn_prev;

        /* Leer switch PAUSE (active high) */
        switch_pause = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_PAUSE_BASE) & 0x1;
        paused = switch_pause;

        /* Si no esta en pausa, generar y enviar muestra */
        if (!paused) {
            /* Esperar espacio en FIFO izquierdo */
            while (alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_LEFT) == 0) {
                ;
            }

            /* Generar muestra segun wave_type */
            if (wave_type == 0) {
                /* Onda sierra */
                sample_buf[0] = (unsigned int)(phase & 0xFFFF);
            }
            else if (wave_type == 1) {
                /* Onda cuadrada */
                if (phase >= 0)
                    sample_buf[0] = (unsigned int)(AMPLITUDE & 0xFFFF);
                else
                    sample_buf[0] = (unsigned int)((-AMPLITUDE) & 0xFFFF);
            }
            else {
                /* Onda triangular */
                static int direction = 1;
                sample_buf[0] = (unsigned int)(phase & 0xFFFF);
                if (direction == 1) {
                    phase += 300;
                    if (phase >= AMPLITUDE)
                        direction = -1;
                }
                else {
                    phase -= 300;
                    if (phase <= -AMPLITUDE)
                        direction = 1;
                }
            }

            /* Enviar la muestra a ambos canales */
            alt_up_audio_write_fifo(audio_dev, sample_buf, 1, ALT_UP_AUDIO_LEFT);
            alt_up_audio_write_fifo(audio_dev, sample_buf, 1, ALT_UP_AUDIO_RIGHT);

            /* Actualizar fase para sierra y cuadrada */
            if (wave_type == 0 || wave_type == 1) {
                phase += 300;
                if (phase > AMPLITUDE)
                    phase = -AMPLITUDE;
            }

            sample_count++;
        }

        /* Actualizar display de tiempo */
        int elapsed_sec = sample_count / SAMPLE_RATE;
        int minutes     = elapsed_sec / 60;
        int seconds     = elapsed_sec % 60;
        int min_tens    = minutes / 10;
        int min_units   = minutes % 10;
        int sec_tens    = seconds / 10;
        int sec_units   = seconds % 10;

        unsigned char code_min2 = seven_seg_digits[min_tens];
        unsigned char code_min1 = seven_seg_digits[min_units];
        unsigned char code_seg2 = seven_seg_digits[sec_tens];
        unsigned char code_seg1 = seven_seg_digits[sec_units];

        IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_MIN2_BASE, code_min2);
        IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_MIN1_BASE, code_min1);
        IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_SEG2_BASE, code_seg2);
        IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_SEG1_BASE, code_seg1);

        /* Delay breve para no saturar CPU (opcional) */
        usleep(1000); /* 1 ms */
    }

    return 0;
}
