#include <Arduino.h>

#include "control.h"
#include "leds.h"
#include "commands.h"

static int ctrl_state;
static int ctrl_step;

void ctrl_setup()
{
  ctrl_set_state(CTRL_STATE_IDLE);
}

void ctrl_set_state(int state)
{
  ctrl_state = state;
  ctrl_step = 0;
}

int ctrl_run_step()
{
  switch (ctrl_state) {
  case CTRL_STATE_START:
    {
      int active_led = ctrl_step/6;
      if (active_led >= leds_get_num()) {
        cmd_run(CMD_START);
        leds_set(0);
      } else {
        leds_set(1<<active_led);
        ctrl_step++;
      }
    }
    break;

  case CTRL_STATE_STOP:
    {
      int active_led = ctrl_step/2;
      if (active_led >= leds_get_num()) {
        cmd_run(CMD_STOP);
        leds_set(0);
      } else {
        leds_set(1<<active_led);
        ctrl_step++;
      }
    }
    break;

  case CTRL_STATE_ERROR:
    {
      if (ctrl_step > 20) {
        leds_set(0);
        ctrl_set_state(CTRL_STATE_IDLE);      
      } else {
        leds_set((ctrl_step & 1) ? 0 : 0xff);
        ctrl_step++;
      }
    }
    break;
  }

  return ctrl_state;
}
