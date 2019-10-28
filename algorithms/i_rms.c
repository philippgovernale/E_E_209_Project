#include "i_rms.h"
#include "../drivers/adc.h"
#include "../conversions.h"
#include "../constants.h"
#include <math.h>

/*returns rms current in 10^-4 A  by first principles*/ 
uint16_t get_rms_current(uint16_t offset_voltage_count){
	uint32_t i_rms = 0;

	for (uint8_t i = 0; i < SAMPLES_PER_WAVE * WAVE_NUM; i++){
		/* we want to calculate rms without offset as the offset changes the rms. Our original current signal does not have an offset*/
		int16_t sample = adc_convert_channel(CURRENT_CHANNEL) - offset_voltage_count;
		i_rms += (uint32_t) sample* (uint32_t) sample ;
	}

	i_rms /= (SAMPLES_PER_WAVE * WAVE_NUM);
	i_rms = sqrt(i_rms) ;
	i_rms = convert_count_to_i_rms(i_rms); // convert to 10^4 A


	return (uint16_t) i_rms;
}