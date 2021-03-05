#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>

#include "usart.h"
#include "pwm.h"

uint8_t i = 0;
unsigned j;
int main(void)
{
	DDRB = 0;
	PORTB = 0;
    USART1_init();
	timer0_init();

    while(1)
    {
		/*
		for(j = 0; j < 20000/2; ++j)
		{
			_delay_us(2);
			OCR0 = i++;
		}
		for(j = 1; j < 20000/3; ++j)
		{
			_delay_us(3);
			OCR0 = i++;
		}
		for(j = 0; j < 20000/4; ++j)
		{
			_delay_us(4);
			OCR0 = i++;
		}
		*/
		/*scanf("%d",&i);
        printf("Read %d\r\n", i);*/
		//printf("%u\r\n",TCNT0);
    }

}


