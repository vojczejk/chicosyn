#include <stdio.h>
#include "ps2.h"

void ps2_init(void)
{
    //Rising edge on interrupt 1
	EICRA |= (1<<ISC11);
    EICRA &= ~(1<<ISC10);
    EIMSK |=(1<<INT1);
    EIFR  |=(1<<INTF1);
}

ISR(INT1_vect)
{
    static unsigned char data;// Holds the received scan code
    static uint8_t edge = 1;
    static uint8_t bitcount = 11;
    if (!edge) // Routine entered at falling edge
    {
        if(bitcount < 11 && bitcount > 2)// Bit 3 to 10 is data. Parity bit,
        {          
            // start and stop bits are ignored.
            data = (data >> 1);
            if(PIND & 0b00000001)
            data = data | 0x80;// Store a �1�
        }

        //Set interrupt on rising edge
        EICRA = (0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (1<<ISC10) | (0<<ISC01) | (0<<ISC00);
        edge = 1;
    } 
    else // Routine entered at rising edge
    {   
        if(--bitcount == 0)// All bits received
        {
            printf("%x\n\r",data);
            bitcount = 11;
            data = 0;
        }
        
        // Set interrupt on falling edge
        EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
        edge = 0;
    }
}