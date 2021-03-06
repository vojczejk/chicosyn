#include <avr/pgmspace.h>

#include "oscillator.h"
#include "lut.h"


oscillator_t g_main_osc;

void osc_init(oscillator_t * osc)
{
    osc->count = 0;
    osc->enable = 0;
    osc->note = 69;
}

void osc_step(oscillator_t * osc)
{
    if(osc->enable)
        osc->count += ((uint32_t)pgm_read_word(&lut_notestep[osc->note]))<<16;
    else
        osc->count = 0;
}

uint8_t osc_out(oscillator_t * osc)
{
    //Sine
    return pgm_read_byte(&lut_sine[(uint8_t)((osc->count/2) >> 24)]);
    //Square
    //return ((uint8_t)((osc->count/2) >> 24) > 0x80) ? 255 : 0;
}