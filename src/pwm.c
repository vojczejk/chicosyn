#include <avr/io.h>
#include "pwm.h"


void timer0_init()
{
    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 16000.000 kHz
    // Mode: Fast PWM top=0xFF
    // OC0 output: Non-Inverted PWM
    // Timer Period: 0.016 ms
    // Output Pulse(s):
    // OC0 Period: 0.016 ms Width: 0 us
    ASSR=0<<AS0;
    TCCR0=(1<<WGM00) | (1<<COM01) | (0<<COM00) | (1<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0x00;
    OCR0=0x00;
    
    //Enable output
	DDRB |= (1 << DDB4);
	PORTB &= !(1 << PORTB4);
}

void output_set(uint8_t val)
{
    OCR0 = val;
}