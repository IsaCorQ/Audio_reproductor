/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'proce' in SOPC Builder design 'audioplay'
 * SOPC Builder design path: ../../audioplay.sopcinfo
 *
 * Generated: Mon Jun 02 09:59:46 CST 2025
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
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00004020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0xf
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00002020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0xf
#define ALT_CPU_NAME "proce"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00002000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00004020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0xf
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00002020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0xf
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00002000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_AUDIO
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG


/*
 * RAM configuration
 *
 */

#define ALT_MODULE_CLASS_RAM altera_avalon_onchip_memory2
#define RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_BASE 0x2000
#define RAM_CONTENTS_INFO ""
#define RAM_DUAL_PORT 1
#define RAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_INIT_CONTENTS_FILE "audioplay_RAM"
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
#define RAM_SIZE_VALUE 8192
#define RAM_SPAN 8192
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
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x48c8
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x48c8
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x48c8
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "audioplay"


/*
 * audio_0 configuration
 *
 */

#define ALT_MODULE_CLASS_audio_0 altera_up_avalon_audio
#define AUDIO_0_BASE 0x48b0
#define AUDIO_0_IRQ 2
#define AUDIO_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_0_NAME "/dev/audio_0"
#define AUDIO_0_SPAN 16
#define AUDIO_0_TYPE "altera_up_avalon_audio"


/*
 * audio_and_video_config_0 configuration
 *
 */

#define ALT_MODULE_CLASS_audio_and_video_config_0 altera_up_avalon_audio_and_video_config
#define AUDIO_AND_VIDEO_CONFIG_0_BASE 0x48a0
#define AUDIO_AND_VIDEO_CONFIG_0_IRQ -1
#define AUDIO_AND_VIDEO_CONFIG_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AUDIO_AND_VIDEO_CONFIG_0_NAME "/dev/audio_and_video_config_0"
#define AUDIO_AND_VIDEO_CONFIG_0_SPAN 16
#define AUDIO_AND_VIDEO_CONFIG_0_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * filtro1 configuration
 *
 */

#define ALT_MODULE_CLASS_filtro1 altera_avalon_pio
#define FILTRO1_BASE 0x4890
#define FILTRO1_BIT_CLEARING_EDGE_REGISTER 0
#define FILTRO1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILTRO1_CAPTURE 0
#define FILTRO1_DATA_WIDTH 1
#define FILTRO1_DO_TEST_BENCH_WIRING 0
#define FILTRO1_DRIVEN_SIM_VALUE 0
#define FILTRO1_EDGE_TYPE "NONE"
#define FILTRO1_FREQ 50000000
#define FILTRO1_HAS_IN 1
#define FILTRO1_HAS_OUT 0
#define FILTRO1_HAS_TRI 0
#define FILTRO1_IRQ -1
#define FILTRO1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILTRO1_IRQ_TYPE "NONE"
#define FILTRO1_NAME "/dev/filtro1"
#define FILTRO1_RESET_VALUE 0
#define FILTRO1_SPAN 16
#define FILTRO1_TYPE "altera_avalon_pio"


/*
 * filtro2 configuration
 *
 */

#define ALT_MODULE_CLASS_filtro2 altera_avalon_pio
#define FILTRO2_BASE 0x4880
#define FILTRO2_BIT_CLEARING_EDGE_REGISTER 0
#define FILTRO2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILTRO2_CAPTURE 0
#define FILTRO2_DATA_WIDTH 1
#define FILTRO2_DO_TEST_BENCH_WIRING 0
#define FILTRO2_DRIVEN_SIM_VALUE 0
#define FILTRO2_EDGE_TYPE "NONE"
#define FILTRO2_FREQ 50000000
#define FILTRO2_HAS_IN 1
#define FILTRO2_HAS_OUT 0
#define FILTRO2_HAS_TRI 0
#define FILTRO2_IRQ -1
#define FILTRO2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FILTRO2_IRQ_TYPE "NONE"
#define FILTRO2_NAME "/dev/filtro2"
#define FILTRO2_RESET_VALUE 0
#define FILTRO2_SPAN 16
#define FILTRO2_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x48c8
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * min1 configuration
 *
 */

#define ALT_MODULE_CLASS_min1 altera_avalon_pio
#define MIN1_BASE 0x4870
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
#define MIN2_BASE 0x4860
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
 * rst configuration
 *
 */

#define ALT_MODULE_CLASS_rst altera_avalon_pio
#define RST_BASE 0x4830
#define RST_BIT_CLEARING_EDGE_REGISTER 0
#define RST_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RST_CAPTURE 0
#define RST_DATA_WIDTH 1
#define RST_DO_TEST_BENCH_WIRING 0
#define RST_DRIVEN_SIM_VALUE 0
#define RST_EDGE_TYPE "NONE"
#define RST_FREQ 50000000
#define RST_HAS_IN 1
#define RST_HAS_OUT 0
#define RST_HAS_TRI 0
#define RST_IRQ -1
#define RST_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RST_IRQ_TYPE "NONE"
#define RST_NAME "/dev/rst"
#define RST_RESET_VALUE 0
#define RST_SPAN 16
#define RST_TYPE "altera_avalon_pio"


/*
 * seg1 configuration
 *
 */

#define ALT_MODULE_CLASS_seg1 altera_avalon_pio
#define SEG1_BASE 0x4850
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
#define SEG2_BASE 0x4840
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
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x4800
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
