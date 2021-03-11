#ifndef NOTE_LUT_H
#define NOTE_LUT_H

#include <avr/pgmspace.h>
#include <stdint.h>


extern const uint32_t lut_notestep [128] PROGMEM;
extern const uint8_t lut_sine [256] PROGMEM;

typedef enum keys_t
{
    //Bottom row
    C0=0,C0s=1,D0=2,D0s=3,E0=4,F0=5,F0s=6,G0=7,G0s=8,A0=9,A0s=10,B0=11,//C1,C1s,D1,D1s,E1,    
    //Top row
    C1=12,C1s=13,D1=14,D1s=15,E1=16,F1=17,F1s=18,G1=19,G1s=20,A1=21,A1s=22,B1=23,C2=24,C2s=25,D2=26,D2s=27,E2=28,F2=29,F2s=30,G2=31,
    
    LIMITER_KEY_ON=32,

    //Bottom row RELEASE
    C0R=33,C0sR=34,D0R=35,D0sR=36,E0R=37,F0R=38,F0sR=39,G0R=40,G0sR=41,A0R=42,A0sR=43,B0R=44,//C1,C1s,D1,D1s,E1,    
    //Top row RELEASE
    C1R=45,C1sR=46,D1R=47,D1sR=48,E1R=49,F1R=50,F1sR=51,G1R=52,G1sR=53,A1R=54,A1sR=55,B1R=56,C2R=57,C2sR=58,D2R=59,D2sR=60,E2R=61,F2R=62,F2sR=63,G2R=64,
    
    LIMITER_KEY_OFF = 65,

    //here go actions
    CMD_TRANSPOSE_UP = 66,
    CMD_TRANSPOSE_DOWN = 67,
    CMD_ARP_TOGGLE = 68,
    CMD_ARP_FAST =69,
    CMD_ARP_SLOW = 70,
    //limiter
    LIMITER_ACTION=71,
    
    /*CMD_SW_MODE = 35,
    CMD_SEL_ARP_SPEED = 36,
    CMD_SEL_ARP_DIR = 37,
    CMD_SEL_ATTACK = 38,
    CMD_SEL_DELAY = 39,
    CMD_SEL_SUSTAIN = 40,
    CMD_SEL_RELEASE = 41,
    CMD_TOGGLE = 42,
    CMD_RESET = 43,
    CMD_SEL_OSC1 = 44,
    CMD_SEL_OSC2 = 45,
    CMD_SEL_OSC3 = 46,
    CMD_INCREASE_COARSE = 47,
    CMD_INCREASE_FINE = 48,
    CMD_DECREASE_COARSE = 49,
    CMD_DECREASE_FINE = 50,
    CMD_SEL_SINE = 51,
    CMD_SEL_TRIANGLE = 52,
    CMD_SEL_SQUARE = 53,
    CMD_SEL_SAW = 54,
    CMD_SEL_OCTAVE = 55,
    CMD_SEL_PULSEW = 59,*/
    //LIMITER_ACTION=60,
    
    NO_KEY = 254,
    //Error value
    ERROR=255
} keys_t;

#endif