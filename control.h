#ifndef CONTROL_H_FILE
#define CONTROL_H_FILE

#include <stdint.h>

enum {
  CTRL_STATE_IDLE,
  CTRL_STATE_RUNNING,
  CTRL_STATE_ERROR,
};

enum {
  CTRL_CMD_START,
  CTRL_CMD_STOP,
};

void ctrl_setup(int num_leds, const int *led_pins);
void ctrl_start_command(int command);
int ctrl_run_step();

#endif /* CONTROL_H_FILE */
