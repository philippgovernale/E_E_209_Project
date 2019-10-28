#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

uint16_t get_timer_count();
void timer_initialise_TC0();
void timer_wait(uint32_t milliseconds);
void timer_initialise_TC1();
void extint_init(uint8_t pin);

#endif /* TIMER_H_ */
