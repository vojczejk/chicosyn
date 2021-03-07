#include <stdio.h>
#include "ps2.h"
#include "oscillator.h"
#include "keyboard.h"

volatile uint8_t flag_in_escape_0 = 0;
volatile uint8_t flag_in_release = 0;
volatile uint8_t g_left_to_ignore = 0;

ring_buffer_t g_ps2_buf;


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
            if(!ring_buffer_is_full(&g_ps2_buf))
                ring_buffer_queue(&g_ps2_buf,(char)data);
            bitcount = 11;
            data = 0;
        }
        
        // Set interrupt on falling edge
        EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
        edge = 0;
    }
}

void ps2_init(void)
{
    //Rising edge on interrupt 1
	EICRA |= (1<<ISC11);
    EICRA &= ~(1<<ISC10);
    EIMSK |=(1<<INT1);
    EIFR  |=(1<<INTF1);

    ring_buffer_init(&g_ps2_buf);
}

keys_t ps2_scan_translate(uint8_t scan_byte)
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
        case 0x0D:
            return CMD_TRANSPOSE_UP;
        case 0x58:
            return CMD_TRANSPOSE_DOWN;
        case 0xF0:
            return KEY_END;
        case 0xE0:
            return KEY_E0;
        case 0xE1:
            return KEY_E1;
        default:
            return ERROR;
    }
    return ERROR;
}
 
void ps2_scancode_runner()
{
    char tmp;
    if(ring_buffer_is_empty(&g_ps2_buf))
        return;

    if(g_left_to_ignore > 0)
    {
        g_left_to_ignore--;
        ring_buffer_dequeue(&g_ps2_buf,&tmp);
        return;
    }

    if(flag_in_release) //f0 was previous code
    {
        ring_buffer_dequeue(&g_ps2_buf,&tmp);
        keys_t key = ps2_scan_translate((uint8_t)tmp);
        //printf("release\r\n");
        if(key < LIMITER_KEY)
        {
            release_key((uint8_t)key);
            //printf("R%u\r\n",key);
            flag_update_osc = 1;
        }
        //nothing else needs releasing, just ignore
        flag_in_release = 0;
    }
    else if(flag_in_escape_0) //e0 was previous code
    {
        //ignore for now
        flag_in_escape_0 = 0;
    }
    else //Starting new scan code
    {
        ring_buffer_dequeue(&g_ps2_buf,&tmp);
        keys_t key = ps2_scan_translate((uint8_t)tmp);
        if(key == KEY_E0)
            flag_in_escape_0 = 1;
        else if(key == KEY_END)
            flag_in_release = 1;
        else if(key == KEY_E1) //Only key with E1 is break. Ignore the rest of it.
            g_left_to_ignore = 7; 
        else if(key < LIMITER_KEY)
        {
            //play a note
            play_key((uint8_t)key);
            flag_update_osc = 1;
            //printf("%u\r\n",key);
        }
        else if(key < LIMITER_ACTION)
        {
            switch (key)
            {
            case CMD_TRANSPOSE_UP:
                command_transpose_up();
                break;
            case CMD_TRANSPOSE_DOWN:
                command_transpose_down();
                break;
            default:
                break;
            }
        }
    }
}