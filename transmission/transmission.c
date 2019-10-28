#include <stdio.h>
#include "transmission.h"
#include "../drivers/uart.h"
#include "../constants.h"

/*returns the magnitude of the number (as a power of 10)*/
static uint32_t max_diviser(uint16_t number)
{
	int diviser = 10;
	while(number/diviser){
		diviser *= 10;
	}
	diviser /= 10;
	return diviser;
}

static void transmit_newline()
{
	uart_transmit_byte(10);
	//uart_transmit_byte(13); /*/r is only for windows, remove for release!*/
}

/*transmits 4 digit number + possible decimal point (counted from most significant figure from 0)*/
void transmit_number(uint8_t decimal_position, uint16_t number, uint8_t num_of_digits)
{
	uint32_t diviser = max_diviser(number);

	for(uint8_t i=0; i < num_of_digits; i++){

		if(i == decimal_position){
			uart_transmit_byte('.');
		}

		uint8_t digit = (number/diviser) % 10;
		digit += ASCII_CONVERSION_CONSTANT;

		uart_transmit_byte(digit);

		diviser /= 10;
	}

}

/*remove for release*/
void transmit_readings(uint16_t reading)
{
	uint32_t diviser = max_diviser(reading);
	while(diviser > 0) {
		uint8_t digit = (reading/diviser) % 10;
		digit += 48;
		uart_transmit_byte(digit);
		diviser /= 10;
		//uart_transmit_byte(63);
	}
}


/*---------------------------------------------------------*/

static void transmit_v_peak(uint16_t v_peak)
{
	printf("%s", "V="); 
	transmit_number(2, v_peak, 4);
	transmit_newline();
}

static void transmit_i_rms(uint16_t i_rms)
{
    printf("%s", "I="); 
	transmit_number(3, i_rms, 4);
	transmit_newline();
}

static void transmit_power(uint16_t p_avg)
{
	printf("%s","P="); 
	transmit_number(1, p_avg, 4);
	transmit_newline();
}

static void transmit_pf(uint16_t pf)
{
	printf("%s", "F=");
	uart_transmit_byte(48);
	transmit_number(0, pf, 3);
	transmit_newline();
}

void transmit_all(uint16_t v_peak, uint16_t i_rms, uint16_t p_avg, uint16_t pf)
{
	transmit_v_peak(v_peak);
	transmit_i_rms(i_rms);
	transmit_power(p_avg);
	transmit_pf(pf);

}
