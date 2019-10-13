/*
 * EE209_Demo_Design_Simple.c
 *
 * Created: 8/09/2018 3:05:55 PM
 * Author : t_sco
 */ 

#include <stdio.h>

#include "drivers/adc.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"

#include "lib_sort/sort.h"

#include "fsm_msd/state_machine.h"

#include "configuration.h"

int main(void)
{
	ADC_initialise();
	GPIO_initialise();
	TIMER_initialise();
	UART_initialise(BAUD_RATE);
	
	// Create the interface needed by the MSD state machine
	struct msd_interface interface = {
		.wait_func = TIMER_wait,
		.convert_channel_func = ADC_convert_channel,
		.button_pressed_func = GPIO_button_pressed,
		.array_sort_func = SORT_array,
	};
	
	FSM_initialise(&interface);
	
	printf("Initialisation complete\r\n");
	
    while (1) 
    {
		FSM_tick();		
	}
}