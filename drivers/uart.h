#ifndef UART_H_
#define UART_H_

void uart_initialise(uint32_t baud_rate);
void uart_transmit_byte(uint8_t byte);

#endif /* UART_H_ */