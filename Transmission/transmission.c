#include "transmission.h"

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
	usart_transmit(10);
	usart_transmit(13); /*/r is only for windows, remove for release!*/
}

/*transmits 4 digit number + possible decimal point (counted from msb)*/
static void transmit_number(uint8_t decimal_position, uint16_t number, uint8_t num_of_digits)
{
	uint32_t diviser = max_diviser(number);

	uint8_t i;
	for(i=0; i < num_of_digits; i++){

		if(i == decimal_position){
			usart_transmit('.');
		}

		uint8_t digit = (number/diviser) % 10;
		digit += 48;

		usart_transmit(digit);

		diviser /= 10;
	}

}

/*---------------------------------------------------------*/

static void transmit_v_peak(uint16_t v_peak)
{
	printf("V="); /*set up printf transmission*/
	transmit_number(2, v_peak, 4);
	transmit_newline();
}

static void transmit_i_rms(uint16_t i_rms)
{
	printf("I="); /*set up printf transmission*/
	transmit_number(1, i_rms, 4);
	transmit_newline();
}

static void transmit_power(uint16_t p_avg)
{
	printf("P="); /*set up printf transmission*/
	transmit_number(2, p_avg, 4);
	transmit_newline();
}

static void transmit_pf(uint16_t pf)
{
	printf("F="); /*set up printf transmission*/
	transmit_number(1, pf, 4);
	transmit_newline();
}

void transmit_all(uint16_t v_peak, uint8_t i_rms, uint8_t p_avg, uint8_t pf)
{
	transmit_v_peak(v_peak);
	transmit_i_rms(i_rms);
	transmit_power(p_avg);
	transmit_pf(pf);

}
