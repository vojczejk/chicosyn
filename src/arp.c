#include "arp.h"
#include "config.h"
#include "common.h"
#include "keyboard.h"
#include "oscillator.h"

uint8_t flag_arpeggio = 0;
uint16_t g_arp_ticks = DEFAULT_ARP_TICKS;
uint16_t g_arp_lastchange = 0;
uint8_t g_arp_step = 0;


void arp_runner()
{
	if(g_keyboard_buffer_cnt > 0)
    {
        //printf("%u\r\n",(g_sample_cnt - g_arp_lastchange));
        if((g_sample_cnt - g_arp_lastchange) > g_arp_ticks)
        {
            g_arp_step = (g_arp_step + 1) % g_keyboard_buffer_cnt;
            //printf("arprun %u\r\n",g_arp_step);

            g_main_osc.note = get_playing_key(g_arp_step) + (g_keyboard_transpose);
		    g_main_osc.enable = 1;

            g_arp_lastchange = g_sample_cnt;
        }
    }
    else
    {
		g_main_osc.enable = 0;
    }
}

void arp_reset()
{
    g_arp_step = 0;
    g_arp_lastchange = g_sample_cnt;
}

void arp_faster()
{
    if(g_arp_ticks > ARP_MIN_TICKS)
        g_arp_ticks -= 1000;
}

void arp_slower()
{
    if(g_arp_ticks < ARP_MAX_TICKS)
        g_arp_ticks += 1000;

}