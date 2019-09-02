#ifdef ARDUINO_LOLIN_D32_PRO

#include <Arduino.h>

#include "engine.h"
#include "comms_ble.h"
#include "comms_dummy.h"
#include "ui_epaper.h"
#include "state_spiffs.h"
#include "state_dummy.h"

UIEPaper ui;
Engine engine;
CommsBLE comms;
StateSPIFFS state;
StateDummy state;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  state.init("/game.save", "/metadata.bin");
  comms.init();
  ui.clear();
  engine = state.load();
  Serial.println("Ready");
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
  //ui.render(engine);
  ui.flush();
}

# endif // ARDUINO_LOLIN_D32_PRO
