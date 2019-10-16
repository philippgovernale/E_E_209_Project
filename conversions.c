#include "conversions.h"

#define OFFSET_VOLTAGE 1700

/*ratio to convert scaled adc voltage range to real range. The ratio is multiplied by 1024
to be more accurate*/
#define DIVIDER_RATIO ((27 + 390)*(uint32_t)1024)/27

#define SHUNT_RESISTANCE 643 /* in mohms*/

#define CURRENT_AMPLIFICATION_UNDO 27000/82

static uint16_t adc_count_to_voltage(uint16_t adc_count)
{
	uint32_t millivolts = (uint32_t)adc_count* (uint32_t)5000 / 1024; /*convert to 32 bit to prevent overflow when multiplying by 5000*/
	return millivolts;
}


uint16_t convert_count_to_i_rms(uint16_t adc_count)
{

	uint16_t adc_voltage = adc_count_to_voltage(adc_count);
	uint16_t i_rms_unshifted = adc_voltage - OFFSET_VOLTAGE;
	uint32_t i_rms_unamplified = i_rms_unshifted * CURRENT_AMPLIFICATION_UNDO;
	uint16_t i_rms = (uint16_t)i_rms_unamplified/SHUNT_RESISTANCE

	return i_rms;
}

uint16_t convert_count_to_v_peak(uint16_t adc_count)
{
	uint16_t adc_voltage = adc_count_to_voltage(adc_count);
	uint16_t v_peak = (uint16_t)((uint32_t)((adc_voltage - OFFSET_VOLTAGE) * DIVIDER_RATIO)/1024);

	return v_peak;
}

uint16_t convert_adc_count_to_mv(uint16_t adc_count)
{
	uint32_t mv = (uint32_t)adc_value * (uint32_t)5000 / 1024;
	return (uint16_t) mv
}
