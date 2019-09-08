#ifdef ARDUINO_LOLIN_D32_PRO

#define CONFIG_CXX_EXCEPTIONS 1
#include "sdkconfig.h"

#include <Arduino.h>

#include "engine.h"
#ifdef COMMS_BLE
#include "comms_ble.h"
#endif
#include "comms_dummy.h"
#include "ui_epaper.h"
#include "state_spiffs.h"
#include "state_dummy.h"

#define MAIN_TAG "main_d32"

UIEPaper *ui;
Engine *engine;
#ifdef COMMS_BLE
CommsBLE *comms;
#else
CommsDummy *comms;
#endif
StateSPIFFS *state;

void setup() {
  //Serial.begin(CONFIG_CONSOLE_UART_BAUDRATE);
  ESP_LOGI(MAIN_TAG, "Initializing...");
  state = new StateSPIFFS();
  engine = new Engine();
  ui = new UIEPaper();

#ifdef COMMS_BLE
  comms = new CommsBLE();
#else
  comms = new CommsDummy();
#endif

  state->init("/game.save", "/metadata.bin");
  comms->init();
  ui->clear();
  engine = state->load();

  ESP_LOGI(MAIN_TAG, "Entering main loop");
}


void loop() {
  engine->loop(comms);
  comms->loop();
  ui->loop();

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
  //ui->render(engine);

  // Appease the watchdog timer
  vTaskDelay(10);
}

# endif // ARDUINO_LOLIN_D32_PRO
