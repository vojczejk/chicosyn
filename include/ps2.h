#ifndef PS2_H
#define PS2_H

#include <avr/interrupt.h>

#include "lut.h"

extern volatile uint8_t flag_process_scancode;
extern volatile uint8_t flag_in_escape_0;
extern volatile uint8_t flag_in_release;

extern volatile uint8_t g_last_scancode;
extern volatile uint8_t g_left_to_ignore;

void ps2_init(void);

void ps2_scancode_runner();



keys_t ps2_scan_translate(uint8_t scan_byte);
keys_t ps2_scan_e0_translate(uint8_t scan_byte);




#endif 