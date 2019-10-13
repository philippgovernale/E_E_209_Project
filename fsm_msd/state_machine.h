/*
 * state_machine.h
 *
 * Created: 8/09/2018 5:21:55 PM
 *  Author: t_sco
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdbool.h>
#include <stdint.h>

typedef uint16_t(*convert_channel_func_t)(uint8_t channel);
typedef bool (*button_pressed_func_t)(void);
typedef void (*wait_func_t)(uint32_t milliseconds);
typedef void (*array_sort_func_t)(bool ascending, uint16_t* array, uint8_t length);

struct msd_interface {
	convert_channel_func_t convert_channel_func;
	button_pressed_func_t button_pressed_func;
	wait_func_t wait_func;
	array_sort_func_t array_sort_func;
};

void FSM_initialise(struct msd_interface* interface_ptr);
void FSM_tick(void);

#endif /* STATE_MACHINE_H_ */