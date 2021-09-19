#include <Arduino.h>
#include <WiFi.h>

#include "commands.h"
#include "control.h"
#include "leds.h"
#include "config.h"

void cmd_setup()
{
  WiFi.begin(wifi_ssid, wifi_pass);

  // blink all LEDs while connecting
  while (WiFi.status() != WL_CONNECTED) {
    leds_set(0xff);
    delay(250);
    leds_set(0);
    delay(100);
  }

  // blink green LED when connected
  for (int i = 0; i < 6; i++) {
    leds_set(1<<(leds_get_num()-1));
    delay(100);
    leds_set(0);
    delay(50);
  }
}

void cmd_run(int command)
{
  WiFiClient client;
  if (! client.connect(server_host, server_port)) {
    ctrl_set_state(CTRL_STATE_ERROR);
    return;
  }

  switch (command) {
  case CMD_START:
    client.print(remote_control_command_start);
    break;

  case CMD_STOP:
    client.print(remote_control_command_stop);
    break;

  default:
    printf("unknown command: %d\n", command);
    break;
  }

  ctrl_set_state(CTRL_STATE_IDLE);
}
