// Run this with
// > pio run -e native
// > .pio/build/native/program

#ifndef ARDUINO_LOLIN_D32_PRO

#include "ui_native.h"
#include "engine.h"
#include "nav.capnp.h"

#include <string>
#include <iostream>

int main(int argc, char** argv) {
  UINative ui;
  ui.clear();
  Engine engine;
  bool ok = true;
  while (ok) {
    nav::Command cmd = ui.nextCommand();
    while (cmd != nav::Command::UNKNOWN) {
     engine.handleInput(cmd);
     cmd = ui.nextCommand();
    }
    ui.clear();
    ui.render(engine);
    ok = ui.flush();
  }
}

#endif // !ARDUINO_LOLIN_D32_PRO
