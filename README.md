# esp32-remote-control
Send keystrokes to Windows using an ESP32

This is an ESP32 project that connects to a [Remote Control
Server](https://github.com/moefh/win-remote-control) running on
Windows and sends pre-defined keystrokes when the buttons are pressed.

## Compilation

```bash
git clone https://github.com/moefh/esp32-remote-control.git
cd esp32-remote-control
cp config.cpp.SAMPLE config.cpp
```

Then edit `config.cpp`, adding your WiFi SSID and password and the IP
address (in your local network) of your Windows PC running
`remote-control.exe`.

