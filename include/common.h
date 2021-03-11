#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

typedef enum selected_t 
{
    MODE,ARP_SPEED,ARP_DIR,ATTACK,
    DELAY,SUSTAIN,RELEASE,OSCILLATOR,
    SINE,TRIANGLE,SQUARE,SAW,
    OCTAVE,PULSEW,VOLUME
} selected_t;

extern uint8_t g_selected_osc;
extern selected_t g_selected_option;
extern volatile uint32_t g_sample_cnt;


#endif