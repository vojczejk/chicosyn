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
#include "arp.h"

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

	for(i = 0; i< 3; ++i)
	{
		osc_init(g_oscillators+i);
	}

	sei();

    while(1)
    {
		ps2_scancode_runner();
		if(flag_arpeggio)
		{
			arp_runner();
		}
		else
		{
			if(flag_update_osc)
			{
				if(g_keyboard_buffer_cnt > 0)
				{/*
					g_main_osc.note = get_playing_key(0) + (g_keyboard_transpose);
					g_sec_osc.note = get_playing_key(0) + (g_keyboard_transpose-12);
					g_tert_osc.note = get_playing_key(0) + (g_keyboard_transpose-24);
					g_main_osc.on = 1;
					g_sec_osc.on = 1;
					g_tert_osc.on = 1;
					*/
					g_oscillators[0].note = get_playing_key(0) + (g_keyboard_transpose);
					g_oscillators[1].note = get_playing_key(0) + (g_keyboard_transpose-12);
					g_oscillators[2].note = get_playing_key(0) + (g_keyboard_transpose-24);
					g_oscillators[0].on = 1;
					g_oscillators[1].on = 1;
					g_oscillators[2].on = 1;
				}
				else
				{
					g_oscillators[0].on = 0;
					g_oscillators[1].on = 0;
					g_oscillators[2].on = 0;
					/*
					g_main_osc.on = 0;
					g_sec_osc.on = 0;
					g_tert_osc.on = 0;
					*/
				}
				flag_update_osc = 0;
			}
		}
    }

}


