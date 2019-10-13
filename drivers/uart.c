/*
 * uart.c
 *
 * Created: 8/09/2018 3:23:33 PM
 *  Author: t_sco
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

static void uart_transmit_byte(uint8_t byte);

static FILE usart_stdout = FDEV_SETUP_STREAM(uart_transmit_byte, NULL, _FDEV_SETUP_WRITE);

void UART_initialise(uint32_t baud_rate)
{
	UCSR0A = 0x00;
	UCSR0B = 0x08;
	UCSR0C = 0x06;
	UBRR0 = 16000000 / (16 * baud_rate) - 1;
	
	stdout = &usart_stdout;
}

void UART_transmit(uint8_t* byte_array, uint32_t byte_array_length)
{
	// Loop through each byte
	for (uint32_t i = 0; i < byte_array_length; i++) {
		// Transmit it via the UART
		uart_transmit_byte(byte_array[i]);
	}
}

static void uart_transmit_byte(uint8_t byte)
{
	// Wait for the UART data register empty flag
	while ((UCSR0A & 0x20) == 0) {
		;
	}
	
	// Put the byte to be sent into the data register
	UDR0 = byte;
}