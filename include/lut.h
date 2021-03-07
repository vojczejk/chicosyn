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
    //limiter
    LIMITER_KEY=32,

    //here go actions
    CMD_TRANSPOSE_UP = 33,
    CMD_TRANSPOSE_DOWN = 34,
    CMD_ARP_TOGGLE = 35,
    CMD_ARP_FAST =36,
    CMD_ARP_SLOW = 37,
    
    //limiter
    LIMITER_ACTION=38,

    //special flag values
    KEY_END=128,
    KEY_E0=129,
    KEY_E1=130,

    //Error value
    ERROR=255
} keys_t;

#endif