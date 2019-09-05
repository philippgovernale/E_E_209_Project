/*
 * ADC_conversion.c
 *
 * Created: 9/5/2019 8:13:42 PM
 * Author : philipp
 */ 

#include <avr/io.h>
#include <stdlib.h>

#define WAVE_SAMPLES 19
#define VOLTAGE_OFFSET 1760
#define VOLTAGE_CHANNEL X // needs to be defined!

void ADC_initialise(void)
{
	ADMUX = 0x40;
	ADCSRA = 0x87;
	ADCSRB = 0x00;
}

//converts ADC and returns result in millivolts
uint16_t ADC_convert_channel_to_millivolts(uint8_t channel)
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
	
	return (uint16_t)millivolts
}

uint16_t get_peak_voltage()
{
	//uint16_t samples[WAVE_SAMPLES];
	uint16_t sample;
	uint16_t sample_amplitude;
	uint16_t max_sample_amplitude = 0;
	
	uint8_t i;
	for(i=0; i < WAVE_SAMPLES; i++){
		sample = ADC_convert_channel_to_millivolts(VOLTAGE_CHANNEL)
		//get maximum amplitude (may be negative part of wave)
		sample_amplitude = abs(VOLTAGE_OFFSET - sample);
		
		if (sample_amplitude > max_sample_amplitude){
			max_sample_amplitude = sample_amplitude;
		}
	}
	return max_sample_amplitude;
}

int main(void)
{
    /* Replace with your application code */
	ADC_initialise();
    while (1) 
    {
		get_peak_voltage()
    }
}

