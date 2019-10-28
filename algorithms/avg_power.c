#include <stdlib.h>
#include "avg_power.h"
#include "../drivers/adc.h"
#include "../constants.h"

/* 
	We have these global variables because inst_pow would need to return two variables. We tried dynamically allocating,
	however allocation would slow down after a couple of allocations even though the variables are being freed
*/
uint32_t inst_power;
uint16_t second_v;

/*returns the instantaneous power using linear approximation*/
static void inst_pow(uint16_t first_v, uint16_t offset_voltage_count)
{
    uint16_t current_r = adc_convert_channel(CURRENT_CHANNEL);
    second_v = adc_convert_channel(VOLTAGE_CHANNEL);

    uint16_t avg_voltage = (first_v + second_v)/2;

    int16_t avg_voltage_unshift =  avg_voltage - offset_voltage_count;
    avg_voltage_unshift *= V_COUNT_TO_VOLTS;

    int16_t current_r_unshift = current_r - offset_voltage_count;
	current_r_unshift *= I_COUNT_TO_AMPS;
    current_r_unshift /= 10; /*convert to same units multiplier as voltage*/
    
    inst_power = ((int32_t)avg_voltage_unshift * (int32_t)current_r_unshift);

}

/*returns average power by first principles (average of instantaneous powers*/
uint16_t get_avg_power(uint16_t offset_voltage_count)
{
	uint16_t first_v = adc_convert_channel(VOLTAGE_CHANNEL);
	int32_t power_sum = 0;
	
	for(uint8_t i=0; i < (WAVE_NUM * SAMPLES_PER_WAVE); i++){
		inst_pow(first_v, offset_voltage_count);
		power_sum += (inst_power);
		/*the second voltage which is set by inst pow needs to be used for the next 
		voltage interpolation*/
		first_v = second_v;
	}
	
	/*divide by thousand converts to W * 10^3*/
	uint16_t avg_power_mw = (uint16_t) (power_sum/ (WAVE_NUM * SAMPLES_PER_WAVE)/1000);
	return avg_power_mw;
}
