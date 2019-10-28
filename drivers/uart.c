#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

static FILE usart_stdout = FDEV_SETUP_STREAM(uart_transmit_byte, NULL, _FDEV_SETUP_WRITE);

void uart_initialise(uint32_t baud_rate)
{
	UCSR0A = 0x00;
	/* enable transmitter*/
	UCSR0B = 0x08;
	/* set 8 bit character size*/
	UCSR0C = 0x06;
	/* set baud rate prescaler*/
	UBRR0 = 16000000 / (16 * baud_rate) - 1;
	
	stdout = &usart_stdout;
}

void uart_transmit_byte(uint8_t byte)
{
	// Wait for the UART data register empty flag
	while ((UCSR0A & 0x20) == 0) {
		;
	}
	
	// Put the byte to be sent into the data register
	UDR0 = byte;
}



