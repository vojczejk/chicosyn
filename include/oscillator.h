#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include  <stdint.h>

#include "config.h"

extern volatile uint8_t flag_update_osc;

typedef struct oscillator_t
{
    uint32_t count;
    uint8_t note;
    uint8_t on;
} oscillator_t;


void osc_init(oscillator_t * osc);
void osc_step(oscillator_t * osc);
uint8_t osc_out(oscillator_t * osc);
/*
extern oscillator_t g_main_osc;
extern oscillator_t g_sec_osc;
extern oscillator_t g_tert_osc;
*/

extern oscillator_t g_oscillators[3];

#endif