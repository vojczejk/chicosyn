#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <stdio.h>

static int uart_putchar(char c, FILE *stream);
static int uart_getchar(FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void USART1_init();
void USART1_write(unsigned char data);
unsigned char USART1_read();

#endif