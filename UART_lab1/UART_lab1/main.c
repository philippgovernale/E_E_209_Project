/*
 * UART_lab1.c
 *
 * Created: 8/1/2019 1:08:44 PM
 * Author : philipp
 */ 

#include <avr/io.h>

#define UBRR 103
#define PRIMES_NO 62

void usart_init(uint8_t ubrr);
void usart_transmit(uint8_t data);

int primes[PRIMES_NO] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};


int main(void)
{
    /* Replace with your application code */
	usart_init(UBRR);
	int prime_count = 0;
	/*usart_transmit(51);*/
	while(prime_count < 62){
		//int remainder;
		int number = primes[prime_count];
		
		int diviser = 100;
		while(diviser > 0){
			if(number /diviser){
				usart_transmit((number/diviser) % 10 + 48);
			}
			diviser /= 10;
			//usart_transmit(remainder+48);
		}
		
		if(prime_count != 61){
			usart_transmit(44);
			usart_transmit(32);
		}
		prime_count++;
		//if(prime_count == PRIMES_NO){
			//prime_count = 0;
		//}
	}
    while (1) 
	{
	;
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

int max_diviser(int number){
	int diviser = 10;
	while(number/diviser){
		diviser *= 10;
	}
	diviser *= 10;
	return diviser;
}

