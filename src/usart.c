#include "usart.h"

void USART1_init()
{
		// Set baud rate
	UBRR1H = 0;
	UBRR1L = 16;
	UCSR1A = (1<<U2X1);
	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	// Set frame format
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);;

    stdin = stdout = &mystdout;
}

void USART1_write(unsigned char data)
{
	// Wait for empty transmit buffer
	while ( !( UCSR1A & (1<<UDRE1)) ) ;
	// Put data into buffer, sends the data
	UDR1 = data;
}

unsigned char USART1_read()
{
	// Wait for data to be received
	while ( !(UCSR1A & (1<<RXC1)) );
	// Get and return received data from buffer
	return UDR1;
}

static int uart_putchar(char c, FILE *stream)
{
    USART1_write(c);
    return 0;
}

static int uart_getchar(FILE *stream)
{
    return USART1_read();
}
