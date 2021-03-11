#ifndef PS2_H
#define PS2_H

#include <avr/interrupt.h>

#include "lut.h"
#include <ringbuffer.h>

extern ring_buffer_t g_ps2_buf;

void ps2_init(void);

void ps2_scancode_runner();


keys_t ps2_scan_translate(uint8_t scan_byte);




#endif 