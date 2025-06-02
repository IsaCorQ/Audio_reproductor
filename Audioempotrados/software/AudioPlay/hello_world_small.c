/*
 * Ejemplo corregido de generacion de onda sierra con debug prints en Nios II
 *
 * Requisitos en Platform Designer:
 *   - IP "Audio Clock for DE-series Boards" conectado a audio_0.clk
 *   - IP "Audio" (altera_up_avalon_audio) configurado a 24 bits (Audio Out habilitado)
 *   - IP "Audio and Video Config" en 24 bits, 48 kHz y "Auto Initialize"
 *
 * Mapear pines en el .qsf:
 *   audio_pll_0_audio_clk                            -> PIN_G7   (AUD_XCK)
 *   audio_0_external_interface.bclk                   -> PIN_H7   (AUD_BCLK)
 *   audio_0_external_interface.lrclk                  -> PIN_H8   (AUD_DACLRCK)
 *   audio_0_external_interface.dato_out               -> PIN_J7   (AUD_DACDAT)
 *   audio_and_video_config_0_external_interface.scl   -> PIN_J12  (I2C_SCLK)
 *   audio_and_video_config_0_external_interface.sda   -> PIN_K12  (I2C_SDAT)
 *
 * El CODEC WM8731 estara listo para recibir datos I2S a 24 bits/48 kHz.
 *
 * Este codigo genera una onda sierra a 480 Hz (48 000 muestras/seg × 100 pasos/ciclo),
 * y emite un mensaje de debug al completar cada ciclo.
 * Compila este archivo en tu proyecto Nios II que incluya los drivers de audio
 * (altera_up_avalon_audio y altera_up_avalon_audio_and_video_config).
 */

#include "system.h"
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "sys/alt_stdio.h"
#include "unistd.h"   // para usleep()

int main()
{
    alt_up_audio_dev * audio_dev;
    int phase;
    const int AMPLITUDE   = 80000;
    const int STEP        = 200;
    const int CYCLE_STEPS = (2 * AMPLITUDE) / STEP;  // (30000 - (-30000)) / 600 = 100
    unsigned int sample_buf[1];
    int cycle_count = 0;

    // 1) Abrir el dispositivo de audio "/dev/audio_0"
    audio_dev = alt_up_audio_open_dev("/dev/audio_0");
    if (audio_dev == NULL) {
        alt_printf("Error: no se encontro /dev/audio_0\n");
        return -1;
    }
    alt_printf("Dispositivo audio_0 abierto.\n");

    // 2) Resetear el core de audio para inicializar el CODEC WM8731
    alt_up_audio_reset_audio_core(audio_dev);
    alt_printf("Audio core reiniciado.\n");
    alt_printf("Generando onda sierra (amplitud = %d, pasos por ciclo = %d)...\n",
               AMPLITUDE, CYCLE_STEPS);

    // 3) Inicializar fase en -AMPLITUDE
    phase = -AMPLITUDE;

    // 4) Loop infinito: generar la onda y escribir al FIFO a ritmo de 48 kHz
    while (1)
    {
        // 4.1) Esperar hasta que haya espacio en el FIFO de transmision (canal izquierdo)
        while (alt_up_audio_write_fifo_space(audio_dev, ALT_UP_AUDIO_LEFT) == 0) {
            ; // espera activa
        }

        // 4.2) Preparar la muestra en el buffer (unsigned int de 16 bits)
        //      El CODEC acepta 16 bits con signo; truncamos phase
        sample_buf[0] = (unsigned int)(phase & 0xFFFF);

        // 4.3) Escribir la misma muestra en FIFO izquierdo y derecho
        alt_up_audio_write_fifo(audio_dev, sample_buf, 1, ALT_UP_AUDIO_LEFT);
        alt_up_audio_write_fifo(audio_dev, sample_buf, 1, ALT_UP_AUDIO_RIGHT);

        // 4.4) Incrementar contador de pasos en el ciclo
        cycle_count++;
        if (cycle_count >= CYCLE_STEPS) {
            // Debug: ciclo completo
            alt_printf("DEBUG: complete_cycle: phase llego a %d, reiniciando a %d\n",
                       phase, -AMPLITUDE);
            cycle_count = 0;
        }

        // 4.5) Incrementar fase y reiniciar si supera el maximo
        phase += STEP;
        if (phase > AMPLITUDE) {
            phase = -AMPLITUDE;
        }

        // 4.6) (Opcional) Pequeño retraso para ceder CPU;
        //      si se omite, el loop corre a 48kHz real (recomendado para audio real)
        // usleep(1);
    }

    return 0;
}
