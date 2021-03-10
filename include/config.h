#ifndef CONFIG_H
#define CONFIG_H

#define MAX(a,b) (((a)>(b))?(a):(b))

//Size of memory for played keys. Maximum of concurrent key presses detected.
#define KEYBOARD_BUFFER_SIZE 16

#define DEFAULT_OCTAVE 4
#define MAX_OCTAVE 6

#define DEFAULT_ARP_TICKS 1200
#define ARP_STEP 100
#define ARP_MIN_TICKS 500
#define ARP_MAX_TICKS 5000

#endif