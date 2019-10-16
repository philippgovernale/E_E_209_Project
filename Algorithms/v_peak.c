#include "v_peak.h"
#include "../conversions.h"
#include "../drivers/adc.h"

#define WAVE_SAMPLES 19 //for 52 us sampling rate
#define VOLTAGE_OFFSET 1760

uint16_t get_peak_voltage()
{
	uint16_t sample;
	uint16_t sample_amplitude;
	uint16_t max_sample_amplitude = 0;

	uint8_t i;
	for (i=0; i < WAVE_SAMPLES; i++) {
		sample = ADC_convert_channel(VOLTAGE_CHANNEL);
		//get maximum amplitude (may be negative part of wave)
		sample_amplitude = abs(VOLTAGE_OFFSET - sample);

		if (sample_amplitude > max_sample_amplitude) {
			max_sample_amplitude = sample_amplitude;
		}
	}
	return adc_count_to_mv(max_sample_amplitude);
}
