#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include  <stdint.h>


typedef struct oscillator_t
{
    uint32_t count;
    uint8_t note;
    uint8_t enable;
} oscillator_t;

void osc_init(oscillator_t * osc);
void osc_step(oscillator_t * osc);
uint8_t osc_out(oscillator_t * osc);


extern oscillator_t g_main_osc;

#endif