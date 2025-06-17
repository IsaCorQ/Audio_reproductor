/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'NIOS2' in SOPC Builder design 'audiosystem'
 * SOPC Builder design path: ../../audiosystem.sopcinfo
 *
 * Generated: Mon Jun 16 10:06:22 CST 2025
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * AUDIO configuration
 *
 */

#define ALT_MODULE_CLASS_AUDIO altera_up_avalon_audio
#define AUDIO_BASE 0x430e0
#define AUDIO_IRQ 2
#define AUDIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_NAME "/dev/AUDIO"
#define AUDIO_SPAN 16
#define AUDIO_TYPE "altera_up_avalon_audio"


/*
 * AUDIOCONFIG configuration
 *
 */

#define ALT_MODULE_CLASS_AUDIOCONFIG altera_up_avalon_audio_and_video_config
#define AUDIOCONFIG_BASE 0x430d0
#define AUDIOCONFIG_IRQ -1
#define AUDIOCONFIG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AUDIOCONFIG_NAME "/dev/AUDIOCONFIG"
#define AUDIOCONFIG_SPAN 16
#define AUDIOCONFIG_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00042820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x13
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00020020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x13
#define ALT_CPU_NAME "NIOS2"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00020000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00042820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x13
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00020020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x13
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00020000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_FIFO
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_AUDIO
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG
#define __ALTERA_UP_AVALON_VIDEO_CHARACTER_BUFFER_WITH_DMA


/*
 * JTAG configuration
 *
 */

#define ALT_MODULE_CLASS_JTAG altera_avalon_jtag_uart
#define JTAG_BASE 0x430f8
#define JTAG_IRQ 0
#define JTAG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_NAME "/dev/JTAG"
#define JTAG_READ_DEPTH 64
#define JTAG_READ_THRESHOLD 8
#define JTAG_SPAN 8
#define JTAG_TYPE "altera_avalon_jtag_uart"
#define JTAG_WRITE_DEPTH 64
#define JTAG_WRITE_THRESHOLD 8


/*
 * RAM configuration
 *
 */

#define ALT_MODULE_CLASS_RAM altera_avalon_onchip_memory2
#define RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_BASE 0x20000
#define RAM_CONTENTS_INFO ""
#define RAM_DUAL_PORT 0
#define RAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_INIT_CONTENTS_FILE "audiosystem_RAM"
#define RAM_INIT_MEM_CONTENT 1
#define RAM_INSTANCE_ID "NONE"
#define RAM_IRQ -1
#define RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_NAME "/dev/RAM"
#define RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define RAM_RAM_BLOCK_TYPE "AUTO"
#define RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define RAM_SINGLE_CLOCK_OP 0
#define RAM_SIZE_MULTIPLE 1
#define RAM_SIZE_VALUE 131072
#define RAM_SPAN 131072
#define RAM_TYPE "altera_avalon_onchip_memory2"
#define RAM_WRITABLE 1


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/JTAG"
#define ALT_STDERR_BASE 0x430f8
#define ALT_STDERR_DEV JTAG
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/JTAG"
#define ALT_STDIN_BASE 0x430f8
#define ALT_STDIN_DEV JTAG
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/JTAG"
#define ALT_STDOUT_BASE 0x430f8
#define ALT_STDOUT_DEV JTAG
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "audiosystem"


/*
 * anterior configuration
 *
 */

#define ALT_MODULE_CLASS_anterior altera_avalon_pio
#define ANTERIOR_BASE 0x43040
#define ANTERIOR_BIT_CLEARING_EDGE_REGISTER 0
#define ANTERIOR_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ANTERIOR_CAPTURE 0
#define ANTERIOR_DATA_WIDTH 1
#define ANTERIOR_DO_TEST_BENCH_WIRING 0
#define ANTERIOR_DRIVEN_SIM_VALUE 0
#define ANTERIOR_EDGE_TYPE "NONE"
#define ANTERIOR_FREQ 50000000
#define ANTERIOR_HAS_IN 1
#define ANTERIOR_HAS_OUT 0
#define ANTERIOR_HAS_TRI 0
#define ANTERIOR_IRQ -1
#define ANTERIOR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ANTERIOR_IRQ_TYPE "NONE"
#define ANTERIOR_NAME "/dev/anterior"
#define ANTERIOR_RESET_VALUE 0
#define ANTERIOR_SPAN 16
#define ANTERIOR_TYPE "altera_avalon_pio"


/*
 * fifo_0 configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_0 altera_avalon_fifo
#define FIFO_0_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_0_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_0_BASE 0x4310c
#define FIFO_0_BITS_PER_SYMBOL 16
#define FIFO_0_CHANNEL_WIDTH 8
#define FIFO_0_ERROR_WIDTH 8
#define FIFO_0_FIFO_DEPTH 16
#define FIFO_0_IRQ -1
#define FIFO_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_0_NAME "/dev/fifo_0"
#define FIFO_0_SINGLE_CLOCK_MODE 1
#define FIFO_0_SPAN 4
#define FIFO_0_SYMBOLS_PER_BEAT 2
#define FIFO_0_TYPE "altera_avalon_fifo"
#define FIFO_0_USE_AVALONMM_READ_SLAVE 1
#define FIFO_0_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_0_USE_AVALONST_SINK 0
#define FIFO_0_USE_AVALONST_SOURCE 0
#define FIFO_0_USE_BACKPRESSURE 1
#define FIFO_0_USE_IRQ 0
#define FIFO_0_USE_PACKET 1
#define FIFO_0_USE_READ_CONTROL 0
#define FIFO_0_USE_REGISTER 0
#define FIFO_0_USE_WRITE_CONTROL 0


/*
 * fifo_1 configuration
 *
 */

#define ALT_MODULE_CLASS_fifo_1 altera_avalon_fifo
#define FIFO_1_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_1_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_1_BASE 0x43108
#define FIFO_1_BITS_PER_SYMBOL 16
#define FIFO_1_CHANNEL_WIDTH 8
#define FIFO_1_ERROR_WIDTH 8
#define FIFO_1_FIFO_DEPTH 16
#define FIFO_1_IRQ -1
#define FIFO_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FIFO_1_NAME "/dev/fifo_1"
#define FIFO_1_SINGLE_CLOCK_MODE 1
#define FIFO_1_SPAN 4
#define FIFO_1_SYMBOLS_PER_BEAT 2
#define FIFO_1_TYPE "altera_avalon_fifo"
#define FIFO_1_USE_AVALONMM_READ_SLAVE 1
#define FIFO_1_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_1_USE_AVALONST_SINK 0
#define FIFO_1_USE_AVALONST_SOURCE 0
#define FIFO_1_USE_BACKPRESSURE 1
#define FIFO_1_USE_IRQ 1
#define FIFO_1_USE_PACKET 1
#define FIFO_1_USE_READ_CONTROL 0
#define FIFO_1_USE_REGISTER 0
#define FIFO_1_USE_WRITE_CONTROL 0


/*
 * filt1 configuration
 *
 */

#define ALT_MODULE_CLASS_filt1 altera_avalon_pio
#define FILT1_BASE 0x43080
#define FILT1_BIT_CLEARING_EDGE_REGISTER 0
#define FILT1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILT1_CAPTURE 0
#define FILT1_DATA_WIDTH 1
#define FILT1_DO_TEST_BENCH_WIRING 0
#define FILT1_DRIVEN_SIM_VALUE 0
#define FILT1_EDGE_TYPE "NONE"
#define FILT1_FREQ 50000000
#define FILT1_HAS_IN 1
#define FILT1_HAS_OUT 0
#define FILT1_HAS_TRI 0
#define FILT1_IRQ -1
#define FILT1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILT1_IRQ_TYPE "NONE"
#define FILT1_NAME "/dev/filt1"
#define FILT1_RESET_VALUE 0
#define FILT1_SPAN 16
#define FILT1_TYPE "altera_avalon_pio"


/*
 * filt2 configuration
 *
 */

#define ALT_MODULE_CLASS_filt2 altera_avalon_pio
#define FILT2_BASE 0x43070
#define FILT2_BIT_CLEARING_EDGE_REGISTER 0
#define FILT2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILT2_CAPTURE 0
#define FILT2_DATA_WIDTH 1
#define FILT2_DO_TEST_BENCH_WIRING 0
#define FILT2_DRIVEN_SIM_VALUE 0
#define FILT2_EDGE_TYPE "NONE"
#define FILT2_FREQ 50000000
#define FILT2_HAS_IN 1
#define FILT2_HAS_OUT 0
#define FILT2_HAS_TRI 0
#define FILT2_IRQ -1
#define FILT2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILT2_IRQ_TYPE "NONE"
#define FILT2_NAME "/dev/filt2"
#define FILT2_RESET_VALUE 0
#define FILT2_SPAN 16
#define FILT2_TYPE "altera_avalon_pio"


/*
 * filt3 configuration
 *
 */

#define ALT_MODULE_CLASS_filt3 altera_avalon_pio
#define FILT3_BASE 0x43030
#define FILT3_BIT_CLEARING_EDGE_REGISTER 0
#define FILT3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILT3_CAPTURE 0
#define FILT3_DATA_WIDTH 1
#define FILT3_DO_TEST_BENCH_WIRING 0
#define FILT3_DRIVEN_SIM_VALUE 0
#define FILT3_EDGE_TYPE "NONE"
#define FILT3_FREQ 50000000
#define FILT3_HAS_IN 1
#define FILT3_HAS_OUT 0
#define FILT3_HAS_TRI 0
#define FILT3_IRQ -1
#define FILT3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILT3_IRQ_TYPE "NONE"
#define FILT3_NAME "/dev/filt3"
#define FILT3_RESET_VALUE 0
#define FILT3_SPAN 16
#define FILT3_TYPE "altera_avalon_pio"


/*
 * filt4 configuration
 *
 */

#define ALT_MODULE_CLASS_filt4 altera_avalon_pio
#define FILT4_BASE 0x43020
#define FILT4_BIT_CLEARING_EDGE_REGISTER 0
#define FILT4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILT4_CAPTURE 0
#define FILT4_DATA_WIDTH 1
#define FILT4_DO_TEST_BENCH_WIRING 0
#define FILT4_DRIVEN_SIM_VALUE 0
#define FILT4_EDGE_TYPE "NONE"
#define FILT4_FREQ 50000000
#define FILT4_HAS_IN 1
#define FILT4_HAS_OUT 0
#define FILT4_HAS_TRI 0
#define FILT4_IRQ -1
#define FILT4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILT4_IRQ_TYPE "NONE"
#define FILT4_NAME "/dev/filt4"
#define FILT4_RESET_VALUE 0
#define FILT4_SPAN 16
#define FILT4_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * min1 configuration
 *
 */

#define ALT_MODULE_CLASS_min1 altera_avalon_pio
#define MIN1_BASE 0x430c0
#define MIN1_BIT_CLEARING_EDGE_REGISTER 0
#define MIN1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MIN1_CAPTURE 0
#define MIN1_DATA_WIDTH 7
#define MIN1_DO_TEST_BENCH_WIRING 0
#define MIN1_DRIVEN_SIM_VALUE 0
#define MIN1_EDGE_TYPE "NONE"
#define MIN1_FREQ 50000000
#define MIN1_HAS_IN 0
#define MIN1_HAS_OUT 1
#define MIN1_HAS_TRI 0
#define MIN1_IRQ -1
#define MIN1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MIN1_IRQ_TYPE "NONE"
#define MIN1_NAME "/dev/min1"
#define MIN1_RESET_VALUE 0
#define MIN1_SPAN 16
#define MIN1_TYPE "altera_avalon_pio"


/*
 * min2 configuration
 *
 */

#define ALT_MODULE_CLASS_min2 altera_avalon_pio
#define MIN2_BASE 0x430b0
#define MIN2_BIT_CLEARING_EDGE_REGISTER 0
#define MIN2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MIN2_CAPTURE 0
#define MIN2_DATA_WIDTH 7
#define MIN2_DO_TEST_BENCH_WIRING 0
#define MIN2_DRIVEN_SIM_VALUE 0
#define MIN2_EDGE_TYPE "NONE"
#define MIN2_FREQ 50000000
#define MIN2_HAS_IN 0
#define MIN2_HAS_OUT 1
#define MIN2_HAS_TRI 0
#define MIN2_IRQ -1
#define MIN2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MIN2_IRQ_TYPE "NONE"
#define MIN2_NAME "/dev/min2"
#define MIN2_RESET_VALUE 0
#define MIN2_SPAN 16
#define MIN2_TYPE "altera_avalon_pio"


/*
 * pausa configuration
 *
 */

#define ALT_MODULE_CLASS_pausa altera_avalon_pio
#define PAUSA_BASE 0x43060
#define PAUSA_BIT_CLEARING_EDGE_REGISTER 0
#define PAUSA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PAUSA_CAPTURE 0
#define PAUSA_DATA_WIDTH 1
#define PAUSA_DO_TEST_BENCH_WIRING 0
#define PAUSA_DRIVEN_SIM_VALUE 0
#define PAUSA_EDGE_TYPE "NONE"
#define PAUSA_FREQ 50000000
#define PAUSA_HAS_IN 1
#define PAUSA_HAS_OUT 0
#define PAUSA_HAS_TRI 0
#define PAUSA_IRQ -1
#define PAUSA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PAUSA_IRQ_TYPE "NONE"
#define PAUSA_NAME "/dev/pausa"
#define PAUSA_RESET_VALUE 0
#define PAUSA_SPAN 16
#define PAUSA_TYPE "altera_avalon_pio"


/*
 * seg1 configuration
 *
 */

#define ALT_MODULE_CLASS_seg1 altera_avalon_pio
#define SEG1_BASE 0x430a0
#define SEG1_BIT_CLEARING_EDGE_REGISTER 0
#define SEG1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG1_CAPTURE 0
#define SEG1_DATA_WIDTH 7
#define SEG1_DO_TEST_BENCH_WIRING 0
#define SEG1_DRIVEN_SIM_VALUE 0
#define SEG1_EDGE_TYPE "NONE"
#define SEG1_FREQ 50000000
#define SEG1_HAS_IN 0
#define SEG1_HAS_OUT 1
#define SEG1_HAS_TRI 0
#define SEG1_IRQ -1
#define SEG1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG1_IRQ_TYPE "NONE"
#define SEG1_NAME "/dev/seg1"
#define SEG1_RESET_VALUE 0
#define SEG1_SPAN 16
#define SEG1_TYPE "altera_avalon_pio"


/*
 * seg2 configuration
 *
 */

#define ALT_MODULE_CLASS_seg2 altera_avalon_pio
#define SEG2_BASE 0x43090
#define SEG2_BIT_CLEARING_EDGE_REGISTER 0
#define SEG2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG2_CAPTURE 0
#define SEG2_DATA_WIDTH 7
#define SEG2_DO_TEST_BENCH_WIRING 0
#define SEG2_DRIVEN_SIM_VALUE 0
#define SEG2_EDGE_TYPE "NONE"
#define SEG2_FREQ 50000000
#define SEG2_HAS_IN 0
#define SEG2_HAS_OUT 1
#define SEG2_HAS_TRI 0
#define SEG2_IRQ -1
#define SEG2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG2_IRQ_TYPE "NONE"
#define SEG2_NAME "/dev/seg2"
#define SEG2_RESET_VALUE 0
#define SEG2_SPAN 16
#define SEG2_TYPE "altera_avalon_pio"


/*
 * siguiente configuration
 *
 */

#define ALT_MODULE_CLASS_siguiente altera_avalon_pio
#define SIGUIENTE_BASE 0x43050
#define SIGUIENTE_BIT_CLEARING_EDGE_REGISTER 0
#define SIGUIENTE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SIGUIENTE_CAPTURE 0
#define SIGUIENTE_DATA_WIDTH 1
#define SIGUIENTE_DO_TEST_BENCH_WIRING 0
#define SIGUIENTE_DRIVEN_SIM_VALUE 0
#define SIGUIENTE_EDGE_TYPE "NONE"
#define SIGUIENTE_FREQ 50000000
#define SIGUIENTE_HAS_IN 1
#define SIGUIENTE_HAS_OUT 0
#define SIGUIENTE_HAS_TRI 0
#define SIGUIENTE_IRQ -1
#define SIGUIENTE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SIGUIENTE_IRQ_TYPE "NONE"
#define SIGUIENTE_NAME "/dev/siguiente"
#define SIGUIENTE_RESET_VALUE 0
#define SIGUIENTE_SPAN 16
#define SIGUIENTE_TYPE "altera_avalon_pio"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x43000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000
#define TIMER_IRQ 1
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999999
#define TIMER_MULT 1.0
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "s"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * vga_char_buffer_avalon_char_buffer_slave configuration
 *
 */

#define ALT_MODULE_CLASS_vga_char_buffer_avalon_char_buffer_slave altera_up_avalon_video_character_buffer_with_dma
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE 0x40000
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_IRQ -1
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_NAME "/dev/vga_char_buffer_avalon_char_buffer_slave"
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_SPAN 8192
#define VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_TYPE "altera_up_avalon_video_character_buffer_with_dma"


/*
 * vga_char_buffer_avalon_char_control_slave configuration
 *
 */

#define ALT_MODULE_CLASS_vga_char_buffer_avalon_char_control_slave altera_up_avalon_video_character_buffer_with_dma
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE 0x43100
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_IRQ -1
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_NAME "/dev/vga_char_buffer_avalon_char_control_slave"
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_SPAN 8
#define VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_TYPE "altera_up_avalon_video_character_buffer_with_dma"

#endif /* __SYSTEM_H_ */
