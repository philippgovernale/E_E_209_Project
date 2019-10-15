/*
 * timer.h
 *
 * Created: 8/09/2018 3:28:56 PM
 *  Author: t_sco
 */


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

void TIMER_initialise(void);
void TIMER_wait(uint32_t milliseconds);

extern volatile uint16_t timer_count;

#endif /* TIMER_H_ */
