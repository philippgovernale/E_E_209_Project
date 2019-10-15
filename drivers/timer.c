/*
 * timer.c
 *
 * Created: 8/09/2018 3:23:01 PM
 *  Author: t_sco
 */

#include <avr/io.h>
#include "timer.h"

extern volatile uint16_t timer_count = 0;
// This function initialises the timer with a 1 millisecond range
void TIMER_initialise(void)
{
	TCCR0A = 0;
	TCCR0B = 0b00000011;
	OCR0A = 250;
}

ISR(INT0_vect){
	TCNT0 = 0;
}

ISR(INT1_vect){
	timer_count = TCNT0;
	TCNT0 = 0;
}

// This function waits for the timer to overflow. An overflow occurs
// every milliseconds. Each overflow it increments a count variable.
// This is continued until the number of milliseconds requested have
// been passed
void TIMER_wait(uint32_t milliseconds)
{
	uint32_t timer_overflows = 0;

	TCNT0 = 0;	// Reset the count

	// Loop until the requested milliseconds have elapsed
	while (timer_overflows < milliseconds) {
		// Check if the timer has overflowed
		if ((TIFR0 & (1 << OCF0A)) != 0) {
			timer_overflows++;		// Increase the count
			TIFR0 |= (1 << OCF0A);	// Reset the overflow flag
		}
	}
}
