#ifndef LEDS_H_FILE
#define LEDS_H_FILE

#include <stdint.h>

bool leds_setup(int num_pins, const int *pins);
void leds_set(uint32_t mask);
int  leds_get_num();

#endif /* LEDS_H_FILE */
