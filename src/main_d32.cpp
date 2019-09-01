#ifdef ARDUINO_LOLIN_D32_PRO

#include <Arduino.h>

#include "engine.h"
#include "comms_ble.h"
#include "ui_epaper.h"

UIEPaper ui;
Engine engine;
CommsBLE comms;

void setup() {
  Serial.begin(115200);
  ui.clear();
  engine = state.load("./test.save");
}

void loop() {
  comms.loop();

  // Handle any inbound messages before handling user input
  message::MessageT msg = comms.receiveMessage();
  if (msg.oneof.type != message::UMessage_NONE) {
    engine.handleMessage(msg);
    return;
  }

  nav::Command cmd = ui.nextCommand();
  while (cmd != nav::Command_unknown) {
   engine.handleInput(cmd, comms);
   cmd = ui.nextCommand();
  }
  ui.clear();
  ui.render(engine);
  ui.flush();
}

# endif // ARDUINO_LOLIN_D32_PRO
