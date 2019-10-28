#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

/* ensure variable is accessible by ISR */
volatile uint16_t timer_count = 0;

/*current zero crossing interrupt*/
ISR(INT0_vect){
	TCNT1 = 0;
}

/*voltage zero crossing interrupt*/
ISR(INT1_vect){
	timer_count = TCNT1;
	TCNT1 = 0;
}

uint16_t get_timer_count(){
	return timer_count;
}

// initialise timer 0 (8 bit) with a 1 millisecond range
void timer_initialise_TC0()
{
	TCCR0A = 0;
	TCCR0B = 0b00000011;
	OCR0A = 250;
}

/* initialise zero crossing interrupts*/
void extint_init(uint8_t pin){
	EIMSK |= (1 << pin);
	
	EICRA &= 0xF0;
	/*intialise both INT0 and INT1 for rising edge*/
	EICRA |= (1 << ISC00);
	EICRA |= (1 << ISC01);
	EICRA |= (1 << ISC10);
	EICRA |= (1 << ISC11);
}


/*Timer 1 (16 bit) initialised with no prescaler*/
void timer_initialise_TC1()
{
	TCCR1A = 0;
	TCCR1B = 1;

}

// This function waits for the timer to overflow. An overflow occurs
// every milliseconds. Each overflow it increments a count variable.
// This is continued until the number of milliseconds requested have
// been passed
void timer_wait(uint32_t milliseconds)
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
