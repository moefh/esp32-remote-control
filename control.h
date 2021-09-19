#ifndef CONTROL_H_FILE
#define CONTROL_H_FILE

#include <stdint.h>

enum {
  CTRL_STATE_IDLE,
  CTRL_STATE_START,
  CTRL_STATE_STOP,
  CTRL_STATE_ERROR,
};

void ctrl_setup();
void ctrl_set_state(int state);
int ctrl_run_step();

#endif /* CONTROL_H_FILE */
