#define F_CPU 16000000UL // Define clockspeed used by MCU for delay library

// Include these libraries
#include <avr/io.h>
#include <util/delay.h>

// Declare functions
static void usart_init(uint32_t ubrr);
static void transmit_prepare(uint32_t data);
static void  get_prime_nums();
static void usart_transmit(uint8_t data);

// Array used for storing prime numbers to transmit
uint16_t primeNums[62];

int main(void){
    usart_init(9600);	// Initialise USART module
	get_prime_nums();	// Get prime numbers to transmit
	
    while (1) 
    {	
		// Transmit each prime number in the format: x, x, x....
		for(int i = 0; i < 62; i++){
			transmit_prepare(primeNums[i]);
			if(i < 61){
				usart_transmit(44);
				usart_transmit(32);
			}
		}
		
		// Display next set of prime numbers on a new line
		usart_transmit(13);
		usart_transmit(10); // newline
	}
}

// Function to set control registers for USART (UART parameters: 9600/8n1)
static void usart_init(uint32_t ubrr){
	UCSR0A = 0x00;
	UCSR0B = 0x08;
	UCSR0C = 0x06;
	UBRR0 = (16000000 / (16 * ubrr)) - 1;	// calculation to set UBRR register so that baud rate is 9600 for give clock frequency
}

// Calculate all the prime numbers under 300

static void get_prime_nums(){
	uint8_t primeNum = 1;
	uint16_t arrayIndex = 0;
	
	// Determines which numbers under 300 are prime numbers
	for(uint16_t count = 2; count < 300; count++){
		for(uint16_t divisor = 2; divisor < count; divisor++){
			if((count % divisor) == 0) {
				primeNum = 0;
				break;
			}
			else {
				primeNum = 1;
			}
		}
		
		// If number is a prime number then store it in primeNums array
		if(primeNum){
			primeNums[arrayIndex] = count;
			arrayIndex++;
		}
	}
}

// Separates and sends individual digits of number in ASCII
static void transmit_prepare(uint32_t data){
	uint32_t check = 1;
	uint32_t divisor = 1;
	
	// Determines largest divisor that puts the number in the highest column of number into ones column
	while(check > 0){
		check = data / divisor;
		divisor = divisor * 10;
	}
	
	divisor = divisor / 100;	// Undo last unnecessary multiplication of divisor in while loop
	
	// for each digit in number...
	while(divisor > 0){
		usart_transmit((data / divisor) + 48);	// Send ASCII equivalent of number to usart_transmit() for transmission
		data -= (data / divisor) * divisor;	// Remove digit just sent from number
		divisor = divisor / 10;	// Adjust divisor to get next digit
	}
}

static void usart_transmit(uint8_t data){
	while((UCSR0A & (1<<UDRE0)) == 0){}	// Wait for USART Data Register Empty flag
	UDR0 = data;	// Put data byte into UDR register so it can be sent via USART connect
}