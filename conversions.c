#include <stdint.h>
#include "conversions.h"
#include "constants.h"


uint16_t convert_adc_count_to_mv(uint16_t adc_count)
{
	uint32_t millivolts = (uint32_t)adc_count* (uint32_t)5000 / 1024; /*convert to 32 bit to prevent overflow when multiplying by 5000*/
	return millivolts;
}


uint16_t convert_count_to_i_rms(uint16_t adc_count)
{

	uint16_t i_rms = adc_count * 34;
	return i_rms;
}

uint16_t convert_count_to_v_peak(uint16_t adc_count)
{
	//uint16_t adc_voltage = convert_adc_count_to_mv(adc_count);
	//uint16_t v_peak = (uint16_t)((uint32_t)((adc_voltage - VOLTAGE_OFFSET_MV) * DIVIDER_RATIO)/1024);
	
	uint16_t v_peak = (uint16_t) (((uint32_t) ((uint32_t) adc_count * (uint32_t) 1024))/ (uint32_t) 282);
	return v_peak;
}
