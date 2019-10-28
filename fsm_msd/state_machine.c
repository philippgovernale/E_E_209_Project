#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../algorithms/i_rms.h"
#include "../algorithms/v_peak.h"
#include "../algorithms/avg_power.h"
#include "../algorithms/pf.h"
#include "../algorithms/offset_voltage.h"

#include "../drivers/timer.h"
#include "../constants.h"
#include "../transmission/transmission.h"

#include "state_machine.h"

enum state {
	STATE_INITIALISATION,
	STATE_V_PEAK,
	STATE_I_RMS,
	STATE_AVG_POWER,
	STATE_POWER_FACTOR,
	STATE_BEGIN_TRANSMISSION,
};


void FSM_tick(void)
{
	static enum state current_state = STATE_V_PEAK;

	uint16_t v_peak = 0;
	uint16_t i_rms = 0;
	uint16_t avg_power = 0;	
	uint16_t pf = 0;
	
	/* obtain an offset voltage for an entire set of transmission*/
	uint16_t offset_voltage_count = get_offset_voltage();

	switch (current_state) {
		case STATE_V_PEAK:
			v_peak = get_v_peak(offset_voltage_count);

		case STATE_I_RMS:
			i_rms = get_rms_current(offset_voltage_count);

		case STATE_AVG_POWER:
			avg_power = get_avg_power(offset_voltage_count);
			
		case STATE_POWER_FACTOR:
			/* allow some time for interrupts to fire before reading count variable*/
			sei();
			timer_wait(30);
			cli();
			pf = get_pf();
			
		case STATE_BEGIN_TRANSMISSION:
			transmit_all(v_peak, i_rms, avg_power, pf);
			break;
		default:
			current_state = STATE_V_PEAK;
			break;
	}
}
