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

uint16_t ADC_convert_channel_to_mv(uint8_t channel)
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

	/* Do we need to do this for every read value? Can't we just do that with our selected ones?*/
	uint32_t millivolts = (uint32_t)adc_value * (uint32_t)5000 / 1024;

	return (uint16_t)millivolts;
}
