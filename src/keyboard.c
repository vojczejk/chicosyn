#include <stdio.h>

#include "keyboard.h"
#include "oscillator.h"
#include "arp.h"

uint8_t g_keyboard_buffer[KEYBOARD_BUFFER_SIZE];
uint8_t g_keyboard_buffer_cnt = 0;
uint8_t g_keyboard_transpose = DEFAULT_OCTAVE*12;

void play_key(uint8_t keyID)
{
    uint8_t i;
    for(i = 0; i < g_keyboard_buffer_cnt; ++i)
    {
        if(g_keyboard_buffer[i] == keyID)
            return;
    }
    insert_playing_key(0,keyID); //Play it with top priority
}

void release_key(uint8_t keyID)
{
    uint8_t i;
    for(i = 0; i < g_keyboard_buffer_cnt; ++i)
    {
        if(g_keyboard_buffer[i] == keyID)
            del_playing_key(i);
    }
}

uint8_t get_playing_key(uint8_t index)
{
    if(index >= g_keyboard_buffer_cnt)
        return 255;

    return g_keyboard_buffer[index];
}

void del_playing_key(uint8_t index)
{
    uint8_t i;
    if(index > g_keyboard_buffer_cnt)
        return;

    for(i = index; i < g_keyboard_buffer_cnt; ++i)
    {
        g_keyboard_buffer[i] = g_keyboard_buffer[i+1];
    }
    g_keyboard_buffer_cnt--;
}

void insert_playing_key(uint8_t index, uint8_t keyID)
{
    uint8_t i,tmp,tmp1;
    if(g_keyboard_buffer_cnt >= KEYBOARD_BUFFER_SIZE ||
       index > g_keyboard_buffer_cnt)
       return;
    
    tmp = keyID; 

    for(i = index; i <= g_keyboard_buffer_cnt; ++i)
    {
        tmp1 = g_keyboard_buffer[i];
        g_keyboard_buffer[i] = tmp;
        tmp = tmp1;
    }
    g_keyboard_buffer_cnt ++;
}


void print_key_buffer()
{
    uint8_t i = 0;
    printf("keybuf %u = ",g_keyboard_buffer_cnt);
    for(i = 0; i < g_keyboard_buffer_cnt; ++i)
    {
        printf("%u ",g_keyboard_buffer[i]);
    }
    printf("\r\n");
}

void command_transpose_up()
{
    if(g_keyboard_transpose < MAX_OCTAVE*12)
        g_keyboard_transpose+=12;
    flag_update_osc = 1;
}

void command_transpose_down()
{
    if(g_keyboard_transpose > 0)
        g_keyboard_transpose-=12;
    flag_update_osc = 1;
}