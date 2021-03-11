#include <stdio.h>
#include "ps2.h"
#include "oscillator.h"
#include "keyboard.h"
#include "arp.h"

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
            //printf("%02x\r\n",data);
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
    static uint8_t e0 = 0, f0 = 0, e1cnt = 0, ret=ERROR;
    if(e1cnt > 0) //Skipping pause-break
    {
        e1cnt--;
        return NO_KEY;
    }
    if(e0)
    {
        //printf("e0 ");
        if(f0)
        {
            //printf("release\r\n");
            ret = ERROR;
        }
        else
        {
            //printf("press\r\n");
            switch(scan_byte)
            {
                case 0x1F: //E0 code
                    ret = CMD_ARP_FAST;
                    break;
                case 0xF0:
                    f0 = 1;
                    return NO_KEY;
                default:
                    ret = ERROR;
            }
        }
    }
    else
    {
        //printf("no e0 ");
        if(f0)
        {
            //printf("release\r\n");
            switch (scan_byte)
            {
                case 0x1A:
                    ret = C0R;
                    break;
                case 0x1B:
                    ret = C0sR;
                    break;
                case 0x22:
                    ret = D0R;
                    break;
                case 0x23:
                    ret = D0sR;
                    break;
                case 0x21:
                    ret = E0R;
                    break;
                case 0x2A:
                    ret = F0R;
                    break;
                case 0x34:
                    ret = F0sR;
                    break;
                case 0x32:
                    ret = G0R;
                    break;
                case 0x33:
                    ret = G0sR;
                    break;
                case 0x31:
                    ret = A0R;
                    break;
                case 0x3B:
                    ret = A0sR;
                    break;
                case 0x3A:
                    ret = B0R;
                    break;
                case 0x41:
                case 0x15:
                    ret = C1R;
                    break;
                case 0x4B:
                case 0x1E:
                    ret = C1sR;
                    break;
                case 0x49:
                case 0x1D:
                    ret = D1R;
                    break;
                case 0x4C:
                case 0x26:
                    ret = D1sR;
                    break;
                case 0x4A:
                case 0x24:
                    ret = E1R;
                    break;
                case 0x2D:
                    ret = F1R;
                    break;
                case 0x2E:
                    ret = F1sR;
                    break;
                case 0x2C:
                    ret = G1R;
                    break;
                case 0x36:
                    ret = G1sR;
                    break;
                case 0x35:
                    ret = A1R;
                    break;
                case 0x3D:
                    ret = A1sR;
                    break;
                case 0x3C:
                    ret = B1R;
                    break;
                case 0x43:
                    ret = C2R;
                    break;
                case 0x46:
                    ret = C2sR;
                    break;
                case 0x44:
                    ret = D2R;
                    break;
                case 0x45:
                    ret = D2sR;
                    break;
                case 0x4D:
                    ret = E2R;
                    break;
                case 0x54:
                    ret = F2R;
                    break;
                case 0x55:
                    ret = F2sR;
                    break;
                case 0x5B:
                    ret = G2R;
                    break;
                default:
                    ret = ERROR;
            }
        }
        else
        {
            //printf("press\r\n");
            switch (scan_byte)
            {
                case 0x1A:
                    ret = C0;
                    break;
                case 0x1B:
                    ret = C0s;
                    break;
                case 0x22:
                    ret = D0;
                    break;
                case 0x23:
                    ret = D0s;
                    break;
                case 0x21:
                    ret = E0;
                    break;
                case 0x2A:
                    ret = F0;
                    break;
                case 0x34:
                    ret = F0s;
                    break;
                case 0x32:
                    ret = G0;
                    break;
                case 0x33:
                    ret = G0s;
                    break;
                case 0x31:
                    ret = A0;
                    break;
                case 0x3B:
                    ret = A0s;
                    break;
                case 0x3A:
                    ret = B0;
                    break;
                case 0x41:
                case 0x15:
                    ret = C1;
                    break;
                case 0x4B:
                case 0x1E:
                    ret = C1s;
                    break;
                case 0x49:
                case 0x1D:
                    ret = D1;
                    break;
                case 0x4C:
                case 0x26:
                    ret = D1s;
                    break;
                case 0x4A:
                case 0x24:
                    ret = E1;
                    break;
                case 0x2D:
                    ret = F1;
                    break;
                case 0x2E:
                    ret = F1s;
                    break;
                case 0x2C:
                    ret = G1;
                    break;
                case 0x36:
                    ret = G1s;
                    break;
                case 0x35:
                    ret = A1;
                    break;
                case 0x3D:
                    ret = A1s;
                    break;
                case 0x3C:
                    ret = B1;
                    break;
                case 0x43:
                    ret = C2;
                    break;
                case 0x46:
                    ret = C2s;
                    break;
                case 0x44:
                    ret = D2;
                    break;
                case 0x45:
                    ret = D2s;
                    break;
                case 0x4D:
                    ret = E2;
                    break;
                case 0x54:
                    ret = F2;
                    break;
                case 0x55:
                    ret = F2s;
                    break;
                case 0x5B:
                    ret = G2;
                    break;
                case 0x0D:
                    ret = CMD_TRANSPOSE_UP;
                    break;
                case 0x58:
                    ret = CMD_TRANSPOSE_DOWN;
                    break;
                case 0x14:
                    ret = CMD_ARP_TOGGLE;
                    break;
                case 0x11:
                    ret = CMD_ARP_SLOW;
                    break;
                case 0xF0:
                    f0 = 1;
                    return NO_KEY;
                case 0xE0:
                    e0 = 1;
                    return NO_KEY;
                case 0xE1:
                    e1cnt = 7; //7 bytes to ignore in pause-break
                    return NO_KEY;
                default:
                    ret = ERROR;
            }
        }
    }
    e0 = 0;
    f0 = 0;
    return ret;
}
 
void ps2_scancode_runner()
{
    char tmp;
    keys_t scanned_key;
    if(ring_buffer_is_empty(&g_ps2_buf))
        return;

    ring_buffer_dequeue(&g_ps2_buf,&tmp);
    scanned_key = ps2_scan_translate(tmp);

    if(scanned_key == NO_KEY || scanned_key == ERROR)
        return;
    
    if(scanned_key < LIMITER_KEY_ON) //Key press
    {
        play_key((uint8_t)scanned_key);
        flag_update_osc = 1;
    }
    else if(scanned_key < LIMITER_KEY_OFF) //Key release
    {
        release_key((uint8_t)scanned_key-C0R);
        flag_update_osc = 1;
    }
    else if(scanned_key < LIMITER_ACTION)
    {
        switch (scanned_key)
        {
        case CMD_TRANSPOSE_UP:
            command_transpose_up();
            break;
        case CMD_TRANSPOSE_DOWN:
            command_transpose_down();
            break;
        case CMD_ARP_TOGGLE:
            flag_arpeggio = !flag_arpeggio;
            break;
        case CMD_ARP_SLOW:
            arp_slower();
            break;
        case CMD_ARP_FAST:
            arp_faster();
            break;
        default:
            break;
        }
    }
    //printf("%u\r\n",scanned_key);
    printf("\r\n"); //TODO Stops working when i remove this printf...wtf
}