/*
 * state_machine.c
 *
 * Created: 8/09/2018 5:21:43 PM
 *  Author: t_sco
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../algorithms/i_rms.h"
#include "../algorithms/v_peak.h"
#include "state_machine.h"

enum state {
	STATE_INITIALISATION,
	STATE_V_PEAK,
	STATE_I_RMS,
	STATE_AVG_POWER,
	STATE_POWER_FACTOR,
	STATE_BEGIN_TRANSMISSION,
};

#define NUMBER_OF_ADC_SAMPLES				10
#define ADC_CONVERSION_FACTOR				2

static uint16_t convert_adc_reading_to_millivolts(uint16_t adc_reading);

struct msd_interface* interface_ptr;

void FSM_initialise(struct msd_interface* interface_in_ptr)
{
	// Do not need this right now
	interface_ptr = interface_in_ptr;
}

void FSM_tick(void)
{
	static enum state current_state = STATE_INITIAL;

	uint16_t v_peak;
	uint16_t i_rms;
	uint16_t avg_power;
	uint16_t power_factor;

	switch (current_state) {
		case STATE_V_PEAK:
			current_state = STATE_I_RMS;
			v_peak = get_v_peak();
			break;
		case STATE_I_RMS:

			i_rms = get_rms_current();

			current_state = STATE_AVG_POWER;
			break;
		case STATE_AVG_POWER:

			current_state = STATE_POWER_FACTOR;
			break;
		case STATE_POWER_FACTOR:
			current_state = STATE_BEGIN_TRANSMISSION;
			break;
		case STATE_BEGIN_TRANSMISSION:
			current_state = STATE_V_PEAK;
			break;
		default:
			current_state = STATE_INITIAL;
			break;
	}
}

static uint16_t convert_adc_reading_to_millivolts(uint16_t adc_reading)
{
	return adc_reading * ADC_CONVERSION_FACTOR;
}
