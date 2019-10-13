/*
 * gpio.h
 *
 * Created: 8/09/2018 3:28:45 PM
 *  Author: t_sco
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>

void GPIO_initialise(void);
bool GPIO_button_pressed(void);

#endif /* GPIO_H_ */