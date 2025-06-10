#include <stdint.h>
#include <string.h>
#include "system.h"

#define FPGA_CHAR_BASE      VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE
#define CHAR_BUF_CTRL_BASE  VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE
#define MSG_RAM_BASE        RAM_BASE

#define VGA_COLS            80
#define VGA_ROWS            30

const char mensaje[] = "Hola Mundo desde VGA!\nEsto es una prueba de visualizacion.\n\nLineas multiples\ncon saltos\nde\nlinea.";

int main(void) {
    // 1) Inicializa front-buffer: REG1=base, REG0=swap
    volatile uint32_t *char_ctrl = (volatile uint32_t *)CHAR_BUF_CTRL_BASE;
    char_ctrl[1] = FPGA_CHAR_BASE;
    char_ctrl[0] = 1;

    // 2) Puntero al buffer VGA
    volatile uint16_t *char_buf  = (volatile uint16_t *)FPGA_CHAR_BASE;

    // 3) Limpia pantalla
    uint16_t blank = (0x02 << 8) | ' ';
    for (int i = 0; i < VGA_COLS * VGA_ROWS; ++i)
        char_buf[i] = blank;

    // 4) Copiar el mensaje a RAM
    volatile char *msg_ram = (volatile char *)MSG_RAM_BASE;
    strcpy((char *)msg_ram, mensaje);

    // 5) Leer el mensaje desde RAM
    volatile const char *msg = (volatile const char *)MSG_RAM_BASE;

    // 6) Calcular número de líneas y longitud de línea máxima
    int lines = 1, max_line_len = 0, current_len = 0;
    for (int i = 0; msg[i] != 0; ++i) {
        if (msg[i] == '\n') {
            if (current_len > max_line_len) max_line_len = current_len;
            current_len = 0;
            lines++;
        } else {
            current_len++;
        }
    }
    if (current_len > max_line_len) max_line_len = current_len;

    // 7) Calcular fila inicial para centrar verticalmente
    int row = (VGA_ROWS - lines) / 2;

    // 8) Mostrar mensaje centrado
    int col = 0;
    for (int i = 0; ; ++i) {
        char c = msg[i];
        if (c == 0)
            break;
        if (c == '\n' || col >= VGA_COLS) {
            col = 0;
            ++row;
            if (row >= VGA_ROWS)
                break;
            if (c == '\n')
                continue;
        }

        // Si es el comienzo de la línea, calcular el centrado horizontal
        if (col == 0) {
            int line_len = 0;
            for (int j = i; msg[j] != 0 && msg[j] != '\n'; ++j)
                line_len++;
            col = (VGA_COLS - line_len) / 2;
        }

        int idx = row * VGA_COLS + col;
        char_buf[idx] = (0x07 << 8) | c;
        ++col;
    }

    // 9) Bucle infinito
    while (1);
    return 0;
}
