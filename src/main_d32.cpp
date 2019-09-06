#ifdef ARDUINO_LOLIN_D32_PRO

#include "sdkconfig.h"

#include <Arduino.h>

#include "engine.h"
#include "comms_ble.h"
#include "comms_dummy.h"
#include "ui_epaper.h"
#include "state_spiffs.h"
#include "state_dummy.h"

#define MAIN_TAG "main_d32"

UIEPaper *ui;
Engine *engine;
CommsBLE *comms;
StateSPIFFS *state;

void setup() {
  //Serial.begin(CONFIG_CONSOLE_UART_BAUDRATE);
  ESP_LOGI(MAIN_TAG, "Initializing...");
  state = new StateSPIFFS();
  engine = new Engine();
  ui = new UIEPaper();
  comms = new CommsBLE();

  state->init("/game.save", "/metadata.bin");
  comms->init();
  ui->clear();
  engine = state->load();

  ESP_LOGI(MAIN_TAG, "Entering main loop");
}


void loop() {
  engine->loop(comms);
  comms->loop();

  // Handle any inbound messages before handling user input
  message::MessageT msg = comms->receiveMessage();
  if (msg.oneof.type != message::UMessage_NONE) {
    engine->handleMessage(msg);
    return;
  }

  nav::Command cmd = ui->nextCommand();
  while (cmd != nav::Command_unknown) {
    ESP_LOGI(MAIN_TAG, "CMD %s", nav::EnumNameCommand(cmd));
    engine->handleInput(cmd, comms);
    cmd = ui->nextCommand();
  }
  //ui->clear();
  //ui->render(engine);
  //ui->flush();
}

# endif // ARDUINO_LOLIN_D32_PRO
