# Rockets N'at

## Setup

- https://docs.platformio.org/en/latest/installation.html#python-package-manager
- https://www.sfml-dev.org/tutorials/2.5/start-linux.php
- https://github.com/google/flatbuffers/releases
- https://github.com/eclipse/paho.mqtt.cpp (requires pajo.mqtt.c lib)
- https://github.com/NVIDIA/nvidia-docker <-- for UI via docker

## Links

- https://docs.platformio.org/en/latest/boards/espressif32/lolin_d32_pro.html
- Photos: https://photos.app.goo.gl/SCY7WTNyaFZkhxnp9
- https://github.com/platformio/platform-espressif32/tree/develop/examples/espidf-arduino-blink <-- example using both espidf and arduino frameworks in platformio

## Notes

https://github.com/nkolban/esp32-snippets/issues/797
Requires commenting out start() in `.platformio/packages/framework-arduinoespressif32/libraries/BLE/src/BLEAdvertising.cpp`


Debug ELF file size:

`xtensa-esp32-elf-size -A firmware.elf`


Lots of griping about unneccessary locale & wchar bundling: https://esp32.com/viewtopic.php?t=3741

```
/home/semartin/.platformio/packages/framework-espidf/components/esp_event/default_event_loop.c: In function 'esp_event_loop_create_default':
/home/semartin/.platformio/packages/framework-espidf/components/esp_event/default_event_loop.c:67:28: error: 'ESP_TASKD_EVENT_STACK' undeclared (first use in this function)

#define ESP_TASKD_EVENT_STACK   CONFIG_SYSTEM_EVENT_TASK_STACK_SIZE
#define ESP_TASKD_EVENT_PRIO   20

```

## Release checklist / QA

- Can trade part from one badge to another
- Name, username, and site are visible on badge screen
- Can launch a ship with all parts, name is auto-generated
- Can select any user coming to the summit
- Can reset device state
- Can send ship on a mission to some local devices
- Hardware
  - All devices have batteries
  - All devices have lanyards
