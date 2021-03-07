#include <avr/pgmspace.h>

#include "oscillator.h"
#include "lut.h"


oscillator_t g_main_osc;

volatile uint8_t flag_update_osc = 0;

void osc_init(oscillator_t * osc)
{
    osc->count = 0;
    osc->enable = 0;
    osc->note = 69;
}

void osc_step(oscillator_t * osc)
{
    if(osc->enable)
        osc->count += ((uint32_t)pgm_read_dword(&lut_notestep[osc->note]));
    else
        osc->count = 0;
}

uint8_t osc_out(oscillator_t * osc)
{   
    uint8_t saw = (uint8_t)(osc->count >> 24);
    if(osc->enable)
    //Saw
        //return saw; 
    //Sine
        //return (pgm_read_byte(&lut_sine[saw]));
    //Square
        return (saw > 0x80) ? 255 : 0;
    //Triangle
        //if(saw < 0x80)
        //    return saw << 1;
        //else
        //    return (0x80 - (saw - 0x80)) << 1;
    else
        return 0x80;
}