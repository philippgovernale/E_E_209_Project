/*
 * adc.h
 *
 * Created: 8/09/2018 3:28:15 PM
 *  Author: t_sco
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_initialise(void);
uint16_t ADC_convert_channel(uint8_t channel);

#endif /* ADC_H_ */
