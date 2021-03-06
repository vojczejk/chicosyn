#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#include "config.h"

extern uint8_t g_keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern uint8_t g_keyboard_buffer_cnt;

void play_key(uint8_t keyID);
void release_key(uint8_t keyID);

uint8_t get_playing_key(uint8_t index);

void del_playing_key(uint8_t index);
void insert_playing_key(uint8_t index, uint8_t keyID);

void print_key_buffer();

#endif