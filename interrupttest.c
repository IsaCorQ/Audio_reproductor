#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"


#define SEG2  SEG1_BASE  // Seconds units
#define SEG1  SEG2_BASE  // Seconds tens
#define MIN2  MIN1_BASE  // Minutes units
#define MIN1  MIN2_BASE  // Minutes tens
#define PAUSE_SW_BASE  PAUSA_BASE  // Address of the pause switch


#define ANTERIOR  ANTERIOR_BASE
#define SIGUIENTE  SIGUIENTE_BASE
#define TIMER   TIMER_BASE

unsigned int elapsed_ms;

void timer_ir_handler (void * context);

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


int main()
{
	volatile unsigned int * anterior_ptr = (unsigned int *) ANTERIOR_BASE;
	volatile unsigned int * siguiente_ptr = (unsigned int *) SIGUIENTE_BASE;
	volatile unsigned int * timer_status_ptr = (unsigned int *) TIMER; //offset 0
	volatile unsigned int * timer_ctr_ptr = timer_status_ptr + 1; //offset 1
	volatile unsigned int * timer_snapl_ptr = timer_status_ptr + 4; //offset 4

	if (*timer_status_ptr != 0) {
		return 0;
	}
	alt_irq_register(TIMER_IRQ, NULL, timer_ir_handler);

	alt_putstr("Turning on the timer\n");
	*timer_ctr_ptr = 0x7;
	while (*timer_status_ptr != 0x2);
	alt_putstr("Timer is running\n");
	elapsed_ms = 0;
	/* Event loop never exits. */
	/* Event loop never exits. */
	while (1) {
		update_display(elapsed_ms);  // Always show the current value
	}



	return 0;
}

void timer_ir_handler(void * context) {
	volatile int* timer_status_ptr = (int *) TIMER;
	*timer_status_ptr = 0x0;  // Clear interrupt

	unsigned int sw = *(volatile unsigned int*) PAUSE_SW_BASE;
	if ((sw & 0x1) == 0) {  // Only count if switch is OFF
		elapsed_ms += 1;
	}

	alt_printf("interrupt handler called.  clear status is %x\n", *timer_status_ptr);
}

