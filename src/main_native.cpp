// Run this with
// > pio run -e native
// > .pio/build/native/program

#ifndef ARDUINO_LOLIN_D32_PRO

#include "ui_native.h"
#include "engine.h"
#include "comms_mq.h"
#include "nav_generated.h"

#include <string>
#include <iostream>

UINative ui;
Engine engine;
CommsMQ comms;

void setup() {
  ui.clear();
}

bool loop() {
  comms.loop();

  // Handle any inbound messages before handling user input
  message::MessageT msg = comms.receiveMessage();
  if (msg.oneof.type != message::UMessage_NONE) {
    engine.handleMessage(msg);
    return true;
  }

  nav::Command cmd = ui.nextCommand();
  while (cmd != nav::Command_unknown) {
   engine.handleInput(cmd, comms);
   cmd = ui.nextCommand();
  }
  ui.clear();
  ui.render(engine);
  return ui.flush();
}

int main(int argc, char** argv) {
  setup();
  while (loop()) {}
}

#endif // !ARDUINO_LOLIN_D32_PRO
