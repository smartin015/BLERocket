/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by pcbreflux
*/

 
/*
   Create a BLE server that will send periodic iBeacon frames.
   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create advertising data
   3. Start advertising.
   4. wait
   5. Stop advertising.
   6. deep sleep
   
*/
#include "sys/time.h"

#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"

#define GPIO_DEEP_SLEEP_DURATION     10  // sleep x seconds and then wake up
RTC_DATA_ATTR static time_t last;        // remember last boot in RTC Memory
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory

#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();
//uint8_t g_phyFuns;

#ifdef __cplusplus
}
#endif

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
BLEAdvertising *pAdvertising;
struct timeval now;

// #define BEACON_PREAMBLE "54ACE" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
// BLEUUID uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";

/* msg format for rocketry: 
    *  TYPE_RACE|RocketConfig
    *  TYPE_TRADE|RocketConfig
    *  TYPE_EXPLORE|RocketConfig
    *  TYPE_SCORE|<uint32_t score>
    * msg format for manufacturing:
    *  TYPE_GIVE|RocketPart
    */
    
typedef enum {
 // Resource messages
 TYPE_GIVE = 0xA0,
 // TYPE_MAKE
 // TYPE_LAUNCH

 // Rocket action messages
 TYPE_RACE = 0xA1,
 TYPE_TRADE = 0xA2,
 TYPE_EXPLORE = 0xA3,

 // Status messages
 TYPE_SCORE = 0xA4
} message_t;

typedef enum {
  PART_HULL = 0,
  PART_THRUSTER = 1,
  PART_C = 2,
  PART_D = 3,
  PART_E = 4
} rocket_part_t;


#define ATTRIBUTE_BITLEN 3
typedef enum {
  ATTRIB_CARGO = 0,
  ATTRIB_SPEED = 1,
  ATTRIB_C = 2, 
  ATTRIB_D = 3,
  ATTRIB_E = 4
} rocket_attr_t;

typedef struct {
  uint8_t cargo : 4;
  uint8_t spd : 3;
  uint8_t c : 3;
  uint8_t d : 3;
  uint8_t e : 3;
} rocket_config_t; // 2 bytes to fully describe a rocket

typedef struct {
  uint8_t len; // always sizeof(rocket_action_msg_t)-1
  message_t msg: 8;
  rocket_config_t rocket;
} rocket_action_msg_t;

void setBeacon() {

  rocket_config_t testRocket;
  testRocket.cargo = 2;
  testRocket.spd = 2;
  testRocket.c = 3;
  testRocket.d = 1;
  testRocket.e = 0;
  
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  setRocketActionMessage(oAdvertisementData, TYPE_RACE, testRocket);

  // Max 31 bytes
  std::string payload = oAdvertisementData.getPayload();
  Serial.print("Payload ");
  for (int i = 0; i < payload.size(); i++) {
    Serial.printf("%02x|", payload[i]);
  }
  Serial.println("");
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
}

void setRocketActionMessage(BLEAdvertisementData& adv, message_t msg, rocket_config_t rocket) {
  char d[5]; d[4] = 0;
  rocket_action_msg_t m;
  m.len = sizeof(rocket_action_msg_t)-1;
  m.msg = msg;
  m.rocket = rocket;
  memcpy(d, &m, sizeof(m));
  
  Serial.print("Msg ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%02x|", d[i]);
  }
  Serial.println("");
  adv.addData(d);
}

void setResourceMessage(BLEAdvertisementData& adv, message_t msg, rocket_part_t part, uint8_t qty) {
  char d[5]; 
  // The length does not include itself but does include everything after it until the next record.  A record
  // with a length value of 0 indicates a terminator.
  d[0] = 3; // packet length
  d[1] = msg;
  d[2] = part;
  d[3] = qty;
  d[4] = 0;
  adv.addData(d);
}

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

  pAdvertising = BLEDevice::getAdvertising();
  
  setBeacon();

   // Start advertising
  pAdvertising->start();
  Serial.println("Advertizing started...");
  delay(100);
  pAdvertising->stop();
  Serial.printf("enter deep sleep\n");
  esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
  Serial.printf("in deep sleep\n");
}

void loop() {
}
