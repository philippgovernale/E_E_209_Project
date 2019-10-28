#include <avr/io.h>
#include "adc.h"

void adc_initialise(void)
{
	/* set AVCC (5V) as ADC voltage reference*/
	ADMUX = 0x40;
	/* set ADC clock prescaler to 128*/ 
	ADCSRA = 0x87;
	ADCSRB = 0x00;
}

uint16_t adc_convert_channel(uint8_t channel)
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
