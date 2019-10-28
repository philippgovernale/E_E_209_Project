/*
 * conversion.h
 *
 * Created: 8/09/2018 10:37:09 PM
 *  Author: Team 14
 */
#include <stdint.h>

#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

uint16_t convert_count_to_i_rms(uint16_t adc_count);
uint16_t convert_count_to_v_peak(uint16_t adc_count);
uint16_t convert_adc_count_to_mv(uint16_t adc_count);


#endif /* CONFIGURATION_H_ */
