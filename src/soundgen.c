#include <stdio.h>

#include "soundgen.h"
#include "oscillator.h"

ring_buffer_t g_audio_buf;

void soundgen_init()
{
    ring_buffer_init(&g_audio_buf);
}

void soundgen_runner()
{
    //If running low on samples, generate in advance
    while(ring_buffer_num_items(&g_audio_buf) < 8)
    {
        gen_sample();
    }
    
    if(!ring_buffer_is_full(&g_audio_buf))
        gen_sample();
}

void gen_sample()
{
    uint8_t tmp;
    osc_step(&g_main_osc);
	tmp = osc_out(&g_main_osc);
    //printf("%u\r\n",tmp);
    ring_buffer_queue(&g_audio_buf,(char)tmp);
}

int8_t pop_sample()
{
    uint8_t tmp;
    if(ring_buffer_dequeue(&g_audio_buf,(char*)&tmp))
        return tmp;
    
    return 0x80;
}