/*
 * gpio.c
 *
 * Created: 8/09/2018 3:23:18 PM
 *  Author: t_sco
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "gpio.h"
#include "../configuration.h"

void GPIO_initialise(void) 
{
	BUTTON_OUTPUT_PORT &= ~(1 << BUTTON_PIN);
}

bool GPIO_button_pressed(void)
{
	return !(BUTTON_INPUT_PORT & (1 << BUTTON_PIN)); // Active low
}