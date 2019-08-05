/*
 * UART_lab1.c
 *
 * Task 4.5
 *
 * Created: 8/1/2019 1:08:44 PM
 * Author : philipp
 */ 

#include <avr/io.h>
#include <stdlib.h>

#define UBRR 103
#define PRIMES_NO 62

void usart_init(uint8_t ubrr);
void usart_transmit(uint8_t data);
int max_diviser(int number);
int* generate_primes(int num_of_primes);


int main(void)
{

	usart_init(UBRR);
	int prime_count = 0;
	int *primes = generate_primes(PRIMES_NO);

    while (1) 
	{
		if(prime_count < PRIMES_NO){
			int number = primes[prime_count];
		
			int diviser = max_diviser(number);
			
			while(diviser > 0){
				usart_transmit((number/diviser) % 10 + 48);
				diviser /= 10;
			}
		
			/*Don't print the last comma and space*/
			if(prime_count != PRIMES_NO -1){
				usart_transmit(44); /*comma*/
				usart_transmit(32); /*space*/
			}
			prime_count++;
		}
    }
	
}

void usart_init(uint8_t ubrr){
	UCSR0A = 0x0;
	UCSR0B = 0x68;
	UCSR0C = 0x6;
	
	/* Clock divider value. Note we sample 16 times per pulse*/
	UBRR0 = UBRR;
	
}

void usart_transmit(uint8_t data){
	
	/*check whether the UDRE0 bit is set to see whether the data register is empty*/
	while((UCSR0A & 0x20) == 0){
		; /*wait*/
	}
	
	UDR0 = data;
}

/*Diviser returns multiple of 10 which depends on the number of digits of the number*/
int max_diviser(int number){
	int diviser = 10;
	while(number/diviser){
		diviser *= 10;
	}
	diviser /= 10;
	return diviser;
}

int* generate_primes(int num_of_primes){
	
	int *primes = malloc(sizeof(int) * num_of_primes);
	int primes_found = 0;
	int num_check = 2;
	int i;

	while(primes_found < num_of_primes)
	{
		int divisers = 0;
		/* loop through numbers and see whether num_check can be divided by them*/
		for(i = num_check-1; i > 1; i--){
			if(num_check % i == 0){
				divisers++;
			}
		}
		/*since we don't include the number itself and 1, if there are no divisers, the number is prime*/
		if(divisers == 0){
			primes[primes_found] = num_check;
			primes_found++;
		}

		num_check++;
	}
	return primes;	
}

