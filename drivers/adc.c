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
	// Set channel
	ADMUX &= 0xF0;
	ADMUX |= channel;

	//Start Conversion
	ADCSRA |= (1 << ADSC);

	//wait for conversion to finish
	while((ADCSRA & (1 << ADIF)) == 0){
		;
	}

	// Get ADC value
	uint16_t adc_value = (ADCL << 0) | (ADCH << 8);

	return adc_value;
}
