#include <stdlib.h>
#include "v_peak.h"
#include "../conversions.h"
#include "../constants.h"
#include "../drivers/adc.h"

/*returns V peak in 10^2 Volts*/
uint16_t get_v_peak(uint16_t offset_voltage_count)
{
	uint16_t sample;
	uint16_t sample_amplitude;
	uint16_t max_sample_amplitude = 0;

	
	for (uint8_t i=0; i < SAMPLES_PER_WAVE * WAVE_NUM; i++) {
		sample = adc_convert_channel(VOLTAGE_CHANNEL);
		//get maximum amplitude (may be negative part of wave)
		sample_amplitude = abs(offset_voltage_count - sample);

		if (sample_amplitude > max_sample_amplitude) {
			max_sample_amplitude = sample_amplitude;
		}
	}
	
	return convert_count_to_v_peak(max_sample_amplitude + offset_voltage_count);
}
