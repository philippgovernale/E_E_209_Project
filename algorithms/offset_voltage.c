#include "../drivers/adc.h"
#include "../constants.h"
#include "offset_voltage.h"

/* returns average of offset counts*/
uint16_t get_offset_voltage()
{
	uint32_t offset_voltage = 0;
	for (uint8_t i=0; i < OFFSET_SAMPLES; i++){
		offset_voltage += adc_convert_channel(OFFSET_VOLTAGE_CHANNEL);
	}
	offset_voltage /= OFFSET_SAMPLES;
	return offset_voltage;
}
