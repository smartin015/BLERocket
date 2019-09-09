// Run this with
// > pio run -e native
// > .pio/build/native/program

#ifndef ARDUINO_LOLIN_D32_PRO

#include "ui_native.h"
#include "engine.h"
#include "comms_mq.h"
#include "state_fs.h"
#include "nav_generated.h"

#include <string>
#include <iostream>

// how long to wait before timing out to nametag
#define IDLE_TIMEOUT_SECS 10


UINative* ui;
Engine* engine;
CommsMQ* comms;
StateFS* state;

static uint64_t lastInputSecs = 0;

void setup() {
  ui = new UINative();
  comms = new CommsMQ();
  state = new StateFS("./data/game.save", "./data/metadata.bin");
  engine = state->load();

  ui->clear();
}

bool loop() {
  engine->loop(comms);
  comms->loop();
  ui->loop();

  // Handle any inbound messages before handling user input
  message::MessageT msg = comms->receiveMessage();
  if (msg.oneof.type != message::UMessage_NONE) {
    engine->handleMessage(msg);
    return true;
  }

  nav::Command cmd = ui->nextCommand();
  while (cmd != nav::Command_unknown) {
   engine->handleInput(cmd, comms);
   cmd = ui->nextCommand();
   lastInputSecs = time(NULL);
  }

  if (lastInputSecs != 0 && lastInputSecs + IDLE_TIMEOUT_SECS < time(NULL)) {
    state->save(engine);
    engine->forceNametag();
    lastInputSecs = 0;
  }

  ui->render(engine);
  return ui->isOpen();
}

int main(int argc, char** argv) {
  setup();
  while (loop()) {}
  state->save(engine);
}

#endif // !ARDUINO_LOLIN_D32_PRO
