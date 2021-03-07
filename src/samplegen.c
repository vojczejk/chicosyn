#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "samplegen.h"
#include "oscillator.h"
#include "soundgen.h"
#include "common.h"

uint16_t g_sample_cnt = 0;

void sampletimer_init()
{

    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 16000.000 kHz
    // Mode: CTC top=OCR1A
    // OC1A output: Disconnected
    // OC1B output: Disconnected
    // OC1C output: Disconnected
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer Period: 0.02 ms
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    // Compare C Match Interrupt: Off
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x01;
    OCR1AL=0x3F;
    OCR1BH=0x00;
    OCR1BL=0x00;
    OCR1CH=0x00;
    OCR1CL=0x00;

/*
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 16000.000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// OC1C output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 0.4 ms
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x18;
OCR1AL=0xFF;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;
*/

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK |= (1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    osc_step(&g_main_osc);
    OCR0 = osc_out(&g_main_osc);
    g_sample_cnt++;
    //printf("%u\r\n",OCR0);
	//OCR0 = pop_sample();
}