#include "control.h"
#include "commands.h"
#include "leds.h"

#define LED_0  15
#define LED_1  4
#define LED_2  5
#define LED_3  21
#define LED_4  23

#define BTN_A  34
#define BTN_B  35

static const int led_pins[] = {
  LED_0, LED_1, LED_2, LED_3, LED_4,
};

void setup()
{
  leds_setup(sizeof(led_pins)/sizeof(led_pins[0]), led_pins);
  ctrl_setup();
  cmd_setup();

  pinMode(BTN_A, INPUT);
  pinMode(BTN_B, INPUT);
}

void loop()
{
  if (ctrl_run_step() == CTRL_STATE_IDLE) {
    if (digitalRead(BTN_A) == 0) ctrl_set_state(CTRL_STATE_START);
    if (digitalRead(BTN_B) == 0) ctrl_set_state(CTRL_STATE_STOP);
  }
  delay(30);
}
