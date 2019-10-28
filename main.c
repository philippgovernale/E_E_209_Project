/*
 * EE209_Demo_Design_Simple.c
 *
 * Created: 8/09/2018 3:05:55 PM
 * Author : Team 14
 */ 

#include <stdio.h>

#include "drivers/adc.h"
#include "drivers/timer.h"
#include "drivers/uart.h"

#include "fsm_msd/state_machine.h"
#include "constants.h"

int main(void)
{
	adc_initialise();
	timer_initialise_TC0();
	timer_initialise_TC1();
	extint_init(ZERO_CROSSING_V_PIN);
	extint_init(ZERO_CROSSING_I_PIN);
	uart_initialise(BAUD_RATE);
	
    while (1) 
    {
		FSM_tick();
	}
}