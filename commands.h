#ifndef COMMANDS_H_FILE
#define COMMANDS_H_FILE

#include <stdint.h>

enum {
  CMD_RET_SUCCESS,
  CMD_RET_ERROR,
};

void cmd_setup();
int cmd_run(const char *command);

#endif /* COMMANDS_H_FILE */
