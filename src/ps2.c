#include <stdio.h>
#include "ps2.h"
#include "oscillator.h"

void ps2_init(void)
{
    //Rising edge on interrupt 1
	EICRA |= (1<<ISC11);
    EICRA &= ~(1<<ISC10);
    EIMSK |=(1<<INT1);
    EIFR  |=(1<<INTF1);
}

keys_t ps2_scan_to_keyboard(uint8_t scan_byte)
{
    switch (scan_byte)
    {
        case 0x1A:
            return C0;
        case 0x1B:
            return C0s;
        case 0x22:
            return D0;
        case 0x23:
            return D0s;
        case 0x21:
            return E0;
        case 0x2A:
            return F0;
        case 0x34:
            return F0s;
        case 0x32:
            return G0;
        case 0x33:
            return G0s;
        case 0x31:
            return A0;
        case 0x3B:
            return A0s;
        case 0x3A:
            return B0;
        case 0x41:
        case 0x15:
            return C1;
        case 0x4B:
        case 0x1E:
            return C1s;
        case 0x49:
        case 0x1D:
            return D1;
        case 0x4C:
        case 0x26:
            return D1s;
        case 0x4A:
        case 0x24:
            return E1;
        case 0x2D:
            return F1;
        case 0x2E:
            return F1s;
        case 0x2C:
            return G1;
        case 0x36:
            return G1s;
        case 0x35:
            return A1;
        case 0x3D:
            return A1s;
        case 0x3C:
            return B1;
        case 0x43:
            return C2;
        case 0x46:
            return C2s;
        case 0x44:
            return D2;
        case 0x45:
            return D2s;
        case 0x4D:
            return E2;
        case 0x54:
            return F2;
        case 0x55:
            return F2s;
        case 0x5B:
            return G2;
        default:
            return KEY_CNT;
    }
    return KEY_CNT;
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
            uint8_t tmp;
            printf("%x\n\r",data);
            tmp = ps2_scan_to_keyboard(data);
            if(tmp != KEY_CNT)
            {
		        g_main_osc.note = (uint8_t)tmp + 60-12-12;
            }
            bitcount = 11;
            data = 0;
        }
        
        // Set interrupt on falling edge
        EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
        edge = 0;
    }
}