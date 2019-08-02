/*
 * UART_lab1.c
 *
 * Created: 8/1/2019 1:08:44 PM
 * Author : philipp
 */ 

#include <avr/io.h>

#define UBRR 103

void usart_init(uint8_t ubrr);
void usart_transmit(uint8_t data);

int main(void)
{
    /* Replace with your application code */
	usart_init(UBRR);
	//usart_transmit(51);

    while (1) 
	{
		int number = 345;
		int remainder;
		for(int i=3; i > 0; i--){
			remainder = number % 10;
			usart_transmit(remainder+48);
			number = number/10;
    }
}

void usart_init(uint8_t ubrr){
	UCSR0A = 0x0;
	UCSR0B = 0x68;
	UCSR0C = 0x6;
	
	/* Clock divider value. Note we sample 16 times per pulse*/
	UBRR0 = ubrr;
	
}

void usart_transmit(uint8_t data){
	
	/*check whether the UDRE0 bit is set to see whether the data register is empty*/
	while((UCSR0A & 0x20) == 0){
		; /*wait*/
	}
	
	UDR0 = data;
}


