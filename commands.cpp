#include <Arduino.h>
#include <WiFi.h>

#include "commands.h"
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

int cmd_run(const char *command)
{
  WiFiClient client;
  if (! client.connect(server_host, server_port)) {
    return CMD_RET_ERROR;
  }

  client.print(remote_control_command_start);
  return CMD_RET_SUCCESS;
}
