#ifndef COMMANDS_H_FILE
#define COMMANDS_H_FILE

#include <stdint.h>

enum {
  CMD_START,
  CMD_STOP,
};

void cmd_setup();
void cmd_run(int command);

#endif /* COMMANDS_H_FILE */
