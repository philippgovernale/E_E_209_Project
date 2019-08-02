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
int diviser(int number);
int* generate_primes(int num_of_primes);

//int primes[PRIMES_NO] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};


int main(void)
{

	usart_init(UBRR);
	int prime_count = 0;

	while(prime_count < PRIMES_NO){
        int *primes = generate_primes(PRIMES_NO);
		int number = primes[prime_count];
		
		int diviser = max_diviser(number);

		usart_transmit((number/diviser) % 10 + 48);
	
		/*Don't print the last comma and space*/
		if(prime_count != PRIMES_NO -1){
			usart_transmit(44);
			usart_transmit(32);
		}
		prime_count++;
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

