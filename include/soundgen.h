#ifndef SOUNDGEN_H
#define SOUNDGEN_H

#include <ringbuffer.h>

extern ring_buffer_t g_audio_buf;

void soundgen_init();

void soundgen_runner();
void gen_sample();

int8_t pop_sample();

#endif