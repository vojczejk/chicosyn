#ifndef ARP_H
#define ARP_H

#include <stdint.h>

extern uint8_t flag_arpeggio;
extern uint32_t g_arp_ticks;
extern uint8_t g_arp_step;
extern uint32_t g_arp_lastchange;

void arp_runner();

void arp_reset();
void arp_faster();
void arp_slower();

#endif