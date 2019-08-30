// Run this with
// > pio run -e native
// > .pio/build/native/program

#ifndef ARDUINO_LOLIN_D32_PRO

#include "ui_native.h"
#include "engine.h"
#include "comms_tcp.h"
#include "nav_generated.h"

#include <string>
#include <iostream>

UINative ui;
Engine engine;
CommsTCP comms("asdf", "ghjk", "cli");

int main(int argc, char** argv) {
  ui.clear();
  bool ok = true;
  while (ok) {
    comms.loop();

    // Handle any inbound messages before handling user input
    auto* msg = comms.receiveMessage();
    if (msg != NULL) {
      engine.handleMessage(*msg);
      continue;
    }

    nav::Command cmd = ui.nextCommand();
    while (cmd != nav::Command_unknown) {
     engine.handleInput(cmd, comms);
     cmd = ui.nextCommand();
    }
    ui.clear();
    ui.render(engine);
    ok = ui.flush();
  }
}

#endif // !ARDUINO_LOLIN_D32_PRO
