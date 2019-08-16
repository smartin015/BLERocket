#include "game.h"
#include "msg.h"
#include "ui.h"

#include "sys/time.h"

#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"

#define GPIO_DEEP_SLEEP_DURATION     10  // sleep x seconds and then wake up
RTC_DATA_ATTR static time_t last;        // remember last boot in RTC Memory
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory


ui_t currentUI = UI_MAIN;

ship_t ship_parts;
ship_t ships[MAX_SHIPS];
uint8_t num_ships = 0;

#define MAX_DEST 5
user_t dests[MAX_DEST];
uint8_t num_dests = 0;

#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();
//uint8_t g_phyFuns;

#ifdef __cplusplus
}
#endif

void deepSleep() {
  Serial.printf("enter deep sleep\n");
  esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
  Serial.printf("in deep sleep\n");
}

void initTestValues() {
// parts[PART_HULL] = 0;
// parts[PART_THRUSTER] = 1;
// parts[PART_C] = 2;
// parts[PART_D] = 3;
// ships[0].cargo = 3;
// ships[0].spd = 2;
// ships[0].c= 2;
// ships[0].d = 2;
// num_ships = 1;
// dests[0] = 123;
// dests[1] = 5;
// num_dests = 2;
}

struct timeval now;
void setup() {
  Serial.begin(115200);
  gettimeofday(&now, NULL);

  Serial.printf("start ESP32 %d\n",bootcount++);
  Serial.printf("deep sleep (%lds since last reset, %lds since last boot)\n",now.tv_sec,now.tv_sec-last);
  last = now.tv_sec;

  // Create the BLE Device
  BLEDevice::init("D32BEACON");
  Serial.println(BLEDevice::getAddress().toString().c_str());
  // 24:0a:c4:9a:a5:de

  initSender();
  initReceiver();

  initTestValues();

  //deepSleep();
}

void loop() {
  doScan();
  //setTestMessage();
  //advertise();
  while (Serial.available()) {
    char c = Serial.read();
    handleInput(c);
  }
  maybeRender(currentUI);
}
