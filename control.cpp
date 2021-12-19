#include <Arduino.h>

#include "control.h"
#include "leds.h"
#include "commands.h"
#include "config.h"

struct COMMAND {
  int command;
  int led_delay;
  const char *command;
};

static const struct COMMAND commands[] = {
  { CTRL_CMD_START, 6, remote_control_command_start },
  { CTRL_CMD_STOP,  2, remote_control_command_stop  },
};

static int ctrl_state;
static int ctrl_cmd_index;
static int ctrl_step;

static void set_state(int state)
{
  ctrl_state = state;
  ctrl_step = 0;
}

void ctrl_setup(int num_leds, const int *led_pins)
{
  leds_setup(num_leds, led_pins);
  cmd_setup();
  set_state(CTRL_STATE_IDLE);
}

void ctrl_start_command(int command)
{
  int cmd_index = -1;
  for (int i = 0; i < (int)(sizeof(commands)/sizeof(commands[0])); i++) {
    if (commands[i].command == command) {
      cmd_index = i;
      break;
    }
  }
  if (cmd_index < 0) return;

  ctrl_cmd_index = cmd_index;
  set_state(CTRL_STATE_RUNNING);
}

int ctrl_run_step()
{
  switch (ctrl_state) {
  case CTRL_STATE_RUNNING:
    {
      const struct COMMAND *cmd = &commands[ctrl_cmd_index];
      int active_led = ctrl_step/cmd->led_delay;
      if (active_led >= leds_get_num()) {
        // run command
        if (cmd_run(cmd->command) == CMD_RET_SUCCESS) {
          set_state(CTRL_STATE_IDLE);
        } else {
          set_state(CTRL_STATE_ERROR);
        }
        leds_set(0);
      } else {
        // blink leds
        leds_set(1<<active_led);
        ctrl_step++;
      }
    }
    break;

  case CTRL_STATE_ERROR:
    {
      if (ctrl_step > 20) {
        leds_set(0);
        set_state(CTRL_STATE_IDLE);
      } else {
        leds_set((ctrl_step & 1) ? 0 : 0xff);
        ctrl_step++;
      }
    }
    break;
  }

  return ctrl_state;
}
