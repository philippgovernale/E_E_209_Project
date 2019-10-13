/*
 * uart.h
 *
 * Created: 8/09/2018 3:28:33 PM
 *  Author: t_sco
 */ 


#ifndef UART_H_
#define UART_H_

void UART_initialise(uint32_t baud_rate);
void UART_transmit(uint8_t* byte_array, uint32_t byte_array_length);

#endif /* UART_H_ */