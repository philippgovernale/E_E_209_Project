/*
 * adc.c
 *
 * Created: 8/09/2018 3:22:50 PM
 *  Author: t_sco
 */ 

#include <avr/io.h>
#include "adc.h"

void ADC_initialise(void)
{
	ADMUX = 0x40;
	ADCSRA = 0x87;
	ADCSRB = 0x00;
}

uint16_t ADC_convert_channel(uint8_t channel)
{
	// Set the channel we wish to convert
	ADMUX &= 0xF0;
	ADMUX |= channel;
	
	// Start the conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for the conversion to finsih
	while ((ADCSRA & (1 << ADIF)) == 0) {
		;
	}
	
	// Read out the ADC counts
	uint16_t adc_count = (ADCL << 0) | (ADCH << 8);
	
	return adc_count;
}