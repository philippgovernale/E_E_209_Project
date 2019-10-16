/*
 * configuration.h
 *
 * Created: 8/09/2018 10:37:09 PM
 *  Author: t_sco
 */

#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

#define BAUD_RATE				9600

#define BUTTON_OUTPUT_PORT		DDRB
#define BUTTON_INPUT_PORT		PINB
#define BUTTON_PIN				7

uint16_t convert_count_to_i_rms(uint16_t adc_count);
uint16_t convert_count_to_v_peak(uint16_t adc_count);
uint16_t convert_adc_count_to_mv(uint16_t adc_count);


#endif /* CONFIGURATION_H_ */
