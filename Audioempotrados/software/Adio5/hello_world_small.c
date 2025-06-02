/*
 * Reproductor modular con tres ondas, filtros y display de tiempo
 *
 * Requisitos en Platform Designer:
 *   - IP "Audio Clock for DE-series Boards" conectado a audio_0.clk
 *   - IP "Audio" (altera_up_avalon_audio) configurado a 24 bits (Audio Out habilitado)
 *   - IP "Audio and Video Config" en modo I2S a 24 bits, 48 kHz y "Auto Initialize"
 *   - PIO para boton NEXT      (SIGUIENTE_BASE)
 *   - PIO para boton PREV      (ANTERIOR_BASE)
 *   - PIO para switch PAUSE    (PAUSA_BASE)
 *   - PIO para switch FILTRO1  (FILTRO1_BASE)
 *   - PIO para switch FILTRO2  (FILTRO2_BASE)
 *   - PIO de salida para cuatro displays de 7 segmentos (anodo comun):
 *       SEG1_BASE, SEG2_BASE, MIN1_BASE, MIN2_BASE
 *
 * Estructura modular:
 *   - init_audio(): abre y resetea el audio
 *   - get_buttons(): lee NEXT, PREV, PAUSA, FILTRO1, FILTRO2
 *   - generate_raw_sample(): genera la muestra bruta segun wave_type
 *   - apply_filters(): aplica filtros basicos a la muestra bruta
 *   - write_fifo(): envía muestra filtrada a los FIFOs de audio
 *   - update_display(): actualiza los cuatro digitos de tiempo
 *
 * El tiempo se cuenta con sample_count (48 000 muestras = 1 segundo real).
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
#define SWITCH_FIL1_BASE     FILTRO1_BASE
#define SWITCH_FIL2_BASE     FILTRO2_BASE

#define SEVENSEG_SEG1_BASE   SEG1_BASE  /* HEX0: unidades de segundos */
#define SEVENSEG_SEG2_BASE   SEG2_BASE  /* HEX1: decenas de segundos */
#define SEVENSEG_MIN1_BASE   MIN1_BASE  /* HEX2: unidades de minutos */
#define SEVENSEG_MIN2_BASE   MIN2_BASE  /* HEX3: decenas de minutos */

#define AMPLITUDE   30000
#define SAMPLE_RATE 48000

/* Tabla de digitos para 7 segmentos (anodo comun)
 * Bits [6:0] = segmentos A-G ( 0 = encendido, 1 = apagado ), bit 7 = punto decimal (apagado=1) */
static const unsigned char seven_seg_digits[10] = {
    0xC0,  /* 0 = 1100 0000 */
    0xF9,  /* 1 = 1111 1001 */
    0xA4,  /* 2 = 1010 0100 */
    0xB0,  /* 3 = 1011 0000 */
    0x99,  /* 4 = 1001 1001 */
    0x92,  /* 5 = 1001 0010 */
    0x82,  /* 6 = 1000 0010 */
    0xF8,  /* 7 = 1111 1000 */
    0x80,  /* 8 = 1000 0000 */
    0x90   /* 9 = 1001 0000 */
};

/* Estructura para botones y switches */
typedef struct {
    int next;      /* 1 = flanco de subida en NEXT */
    int prev;      /* 1 = flanco de subida en PREV */
    int pause;     /* 1 = en pausa */
    int fil1;      /* 1 = filtro 1 activo */
    int fil2;      /* 1 = filtro 2 activo */
} Controls;

/* Abre y reinicia el core de audio, devuelve el puntero dev */
static alt_up_audio_dev * init_audio(void)
{
    alt_up_audio_dev * dev = alt_up_audio_open_dev("/dev/audio_0");
    if (dev == NULL) {
        alt_printf("Error: no se encontro /dev/audio_0\n");
        return NULL;
    }
    alt_printf("Audio_0 abierto.\n");
    alt_up_audio_reset_audio_core(dev);
    alt_printf("Audio core reiniciado.\n");
    return dev;
}

/* Lee botones y switches; detecta flanco de subida para NEXT y PREV */
static void get_buttons(Controls * c, int * prev_next, int * prev_prev)
{
    int raw_next  = IORD_ALTERA_AVALON_PIO_DATA(NEXT_BTN_BASE)   & 0x1;
    int raw_prev  = IORD_ALTERA_AVALON_PIO_DATA(PREV_BTN_BASE)   & 0x1;
    int raw_pause = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_PAUSE_BASE) & 0x1;
    int raw_fil1  = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_FIL1_BASE)  & 0x1;
    int raw_fil2  = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_FIL2_BASE)  & 0x1;

    c->next  = (raw_next  && !(*prev_next))  ? 1 : 0;
    c->prev  = (raw_prev  && !(*prev_prev))  ? 1 : 0;
    c->pause = raw_pause;
    c->fil1  = raw_fil1;
    c->fil2  = raw_fil2;

    *prev_next = raw_next;
    *prev_prev = raw_prev;
}

/* Genera una muestra bruta (int) segun wave_type y modifica phase cuando corresponda */
static int generate_raw_sample(int wave_type, int * phase_ptr)
{
    int ph = *phase_ptr;
    int raw = 0;

    if (wave_type == 0) {
        /* Onda sierra */
        raw = ph;
    }
    else if (wave_type == 1) {
        /* Onda cuadrada */
        raw = (ph >= 0) ? AMPLITUDE : -AMPLITUDE;
    }
    else {
        /* Onda triangular */
        static int direction = 1;
        raw = ph;
        if (direction == 1) {
            ph += 300;
            if (ph >= AMPLITUDE) {
                direction = -1;
            }
        }
        else {
            ph -= 300;
            if (ph <= -AMPLITUDE) {
                direction = 1;
            }
        }
    }

    /* Actualizar fase para sierra y cuadrada */
    if (wave_type == 0 || wave_type == 1) {
        ph += 300;
        if (ph > AMPLITUDE) {
            ph = -AMPLITUDE;
        }
    }

    *phase_ptr = ph;
    return raw;
}

/* Aplica filtros simples a raw_sample; retorna muestra filtrada */
static int apply_filters(int raw_sample, int * last_raw_sample, int fil1, int fil2)
{
    int result = raw_sample;

    if (fil1) {
        /* Filtro 1: promedio con muestra anterior */
        result = (raw_sample + *last_raw_sample) / 2;
    }
    if (fil2) {
        /* Filtro 2: inversion de fase */
        result = -result;
    }

    *last_raw_sample = raw_sample;
    return result;
}

/* Envía muestra filtrada (intenombrada) a FIFO de audio */
static void write_fifo(alt_up_audio_dev * dev, int filtered_sample)
{
    unsigned int buf[1];
    buf[0] = (unsigned int)(filtered_sample & 0xFFFF);

    /* Esperar espacio en FIFO izquierdo */
    while (alt_up_audio_write_fifo_space(dev, ALT_UP_AUDIO_LEFT) == 0) {
        ;
    }
    alt_up_audio_write_fifo(dev, buf, 1, ALT_UP_AUDIO_LEFT);
    alt_up_audio_write_fifo(dev, buf, 1, ALT_UP_AUDIO_RIGHT);
}

/* Actualiza los cuatro displays HEXn con el tiempo elapsed_sec real */
static void update_display(int elapsed_samples)
{
    int elapsed_sec = elapsed_samples / SAMPLE_RATE;  /* convertido a segundos reales */
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
}

int main()
{
    alt_up_audio_dev * audio_dev;
    int phase;
    int wave_type = 0;        /* 0 = sierra, 1 = cuadrada, 2 = triangular */
    int prev_wave_type = 0;
    int sample_count = 0;     /* conteo de muestras reproducidas */
    int btn_next_prev = 0;
    int btn_prev_prev = 0;
    Controls ctrl;
    int last_raw_sample = 0;  /* para filtro 1 */

    /* Inicializar audio */
    audio_dev = init_audio();
    if (audio_dev == NULL) {
        return -1;
    }

    /* Inicializar fase en valor mínimo */
    phase = -AMPLITUDE;

    /* Inicializar displays a 00:00 */
    IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_SEG1_BASE, seven_seg_digits[0]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_SEG2_BASE, seven_seg_digits[0]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_MIN1_BASE, seven_seg_digits[0]);
    IOWR_ALTERA_AVALON_PIO_DATA(SEVENSEG_MIN2_BASE, seven_seg_digits[0]);

    while (1)
    {
        /* Leer botones y switches */
        get_buttons(&ctrl, &btn_next_prev, &btn_prev_prev);

        /* Si cambiamos onda (NEXT o PREV), reiniciar conteo y fase */
        if (ctrl.next) {
            wave_type = (wave_type + 1) % 3;
        }
        if (ctrl.prev) {
            wave_type = (wave_type + 2) % 3;  /* equivale a -1 mod 3 */
        }
        if (wave_type != prev_wave_type) {
            sample_count = 0;
            phase = -AMPLITUDE;
            last_raw_sample = 0;
            prev_wave_type = wave_type;
        }

        /* Si no está en pausa, generar y enviar muestra */
        if (!ctrl.pause) {
            int raw = generate_raw_sample(wave_type, &phase);
            int filtered = apply_filters(raw, &last_raw_sample, ctrl.fil1, ctrl.fil2);
            write_fifo(audio_dev, filtered);
            sample_count++;
        }

        /* Actualizar display de tiempo basándose en sample_count */
        update_display(sample_count);

        /* No se requiere usleep: el bucle se regula con el FIFO a 48 kHz */
    }

    return 0;
}
