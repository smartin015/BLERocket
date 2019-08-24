// Run this with
// > pio run -e native
// > .pio/build/native/program

#ifndef ARDUINO_LOLIN_D32_PRO

#include "ui_native.h"
#include "game.h"
#include "actions.capnp.h"

#include <string>
#include <iostream>

int main(int argc, char** argv) {
  UINative ui;
  Game game;
  while (ui.render(&game)) {
    Command cmd = ui.nextCommand();
    while (cmd != Command::UNKNOWN) {
     game.update(cmd);
     cmd = ui.nextCommand();
    }
  }
}

#endif // !ARDUINO_LOLIN_D32_PRO
