/*
 * labOnePart2.c
 *
 * Created: 1/08/2019 1:22:40 PM
 * Author : jeva126
 */ 

#include <avr/io.h>
#include <stdlib.h>

#define UBRR 103 // Macro 
#define PRIMES_NO 62 // Macro



// This function initializes the UART for a specific baud rate
void usart_init(uint16_t ubrr)
{
	UCSR0A = 0x00; //All 0
	UCSR0B = 0x68;
	UCSR0C = 0x06;
	UBRR0 = ubrr; // 103	
}

// This function transmits a single byte via the UART
void usart_transmit(uint8_t data)
{
	// Wait for the UART data register empty flag
	while ((UCSR0A & 0x20) == 0) {
		;
	}
	// Put the byte to be sent into the data register
	UDR0 = data;
}


int main(void)
{
	
	usart_init(UBRR); 
	
	int number; 
	int remainder;
	int remPlusASCII;

	int primeList[62]; // Array stores prime numbers
	int listPos = 0; // Records current position in list
	int curNum = 2; // Current number testing if it is prime
	int j;
	int primeCheck;
	   
// This code generates an array of prime numbers up to 300
// **********************************************************************
	   while (listPos < 62){
		   primeCheck = 1;
		   j = 2;
		   while (j < curNum){
			   
			   if ((curNum % j) == 0){
				   
				   primeCheck = 0;
			   }
			   
			   j++;
		   }
		   
		   if (primeCheck == 1){
			   primeList[listPos] = curNum;
			   listPos++;
		   }
		   curNum++;

	   }
// **********************************************************************
	   	
	  int loopStop = 0; // Prevents the program from running infinitely
	  int digitCount; // Number of digits of the current prime number to be transmitted
	  int digitHolder[3]; // For multi-digit prime numbers, used to rearrange the order of transmission
	
    while (1) 
    {
		
		while(loopStop == 0){
		
			for (int i = 0; i < 62 ; i++){
				number = primeList[i];
				
				digitCount = 0; // Reset digit count for each prime number ( will be 1, 2 or 3)
				while (number > 0){
					remainder = number % 10;
					remPlusASCII = remainder + 48;
					
					number = number / 10;
				
					digitHolder[digitCount] = remPlusASCII; // Fill the array with each digit of the prime number
					
					digitCount++;
				}
				
// The following code re arranges the order in which we transmit the digits (so they are not reversed)
//*************************************************************************************************
				if(digitCount == 1){
					
					usart_transmit(digitHolder[0]);
				
				} else if(digitCount == 2){
					
					for(int iTwo = 1; iTwo >= 0; iTwo--){
						usart_transmit(digitHolder[iTwo]);
					}
										
				} else if(digitCount == 3){
					
					for(int iThree = 2; iThree >= 0; iThree--){	
						usart_transmit(digitHolder[iThree]);
					}
				}
				
//************************************************************************************************

			// Removes comma and space on the last prime number		
			if(i != 61){
				usart_transmit(',');
				usart_transmit(' ');
			}
				
				
			
			
			}
		loopStop = 1;
		
		}
	}
}

