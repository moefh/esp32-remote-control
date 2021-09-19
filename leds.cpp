#include <Arduino.h>

#include "leds.h"

#define MAX_LEDS 8

static int num_leds;
static unsigned char led_pins[MAX_LEDS];

bool leds_setup(int num, const int *pins)
{
  if (num > MAX_LEDS) {
    return false;
  }
  num_leds = num;

  for (int i = 0; i < num; i++) {
    led_pins[i] = pins[i];
    pinMode(led_pins[i], OUTPUT);
  }
  return true;
}

int leds_get_num()
{
  return num_leds;
}

void leds_set(uint32_t mask)
{
  for (int i = 0; i < num_leds; i++) {
    digitalWrite(led_pins[i], (mask & (1<<i)) != 0);
  }
}
