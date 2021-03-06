#include <avr/io.h>
#include <stdio.h>
//#include <avr/delay.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "pwm.h"
#include "ps2.h"
#include "samplegen.h"
#include "oscillator.h"
#include "keyboard.h"

uint8_t i = 0;
unsigned j;
int main(void)
{
	//Timer interrupt disable
	TIMSK = 0;
	ETIMSK = 0;
	//External interrupts disable
	EICRA = 0;
    EICRA = 0; 
    EIMSK = 0;
    EIFR  = 0;
	//Used ports disable
	DDRB = 0;
	PORTB = 0;
	DDRD = 0;
	PORTD = 0;
    USART1_init();
	timer0_init();
	ps2_init();
	sampletimer_init();

	osc_init(&g_main_osc);
	g_main_osc.enable = 1;

	sei();

    while(1)
    {
		ps2_scancode_runner();

		if(flag_update_osc)
		{
			if(g_keyboard_buffer_cnt > 0)
			{
				g_main_osc.note = get_playing_key(0);
				g_main_osc.enable = 1;
			}
			else
			{
				g_main_osc.enable = 0;
			}
			flag_update_osc = 0;
		}
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
		/*static uint8_t bold, dold;
		if(bold != (PINB & 0b11101111) || dold != PIND)
			printf("%02x -> %02x,%02x -> %02x\r\n",bold, PINB & 0b11101111,dold,PIND);
		bold = PINB & 0b11101111;
		dold = PIND;*/
    }

}


