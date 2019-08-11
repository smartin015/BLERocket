/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

BLEAddress match("24:0a:c4:9a:a5:de");

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

typedef struct {
  uint8_t cargo : 4;
  uint8_t spd : 3;
  uint8_t c : 3;
  uint8_t d : 3;
  uint8_t e : 3;
} rocket_config_t; // 2 bytes to fully describe a rocket

typedef struct {
  message_t msg : 8;
  rocket_config_t rocket;
} rocket_action_msg_t;

rocket_action_msg_t handleRocketActionMessage(uint8_t* ptr) {
  char d[5]; 
  rocket_action_msg_t result;
  memcpy(&result, ptr, sizeof(rocket_action_msg_t));
  Serial.printf("Got rocket action, msg %02x cargo %d speed %d c %d d %d e %d \n", 
    result.msg, 
    result.rocket.cargo, 
    result.rocket.spd,
    result.rocket.c, 
    result.rocket.d, 
    result.rocket.e);
  return result;
}

void parseAdvertisement(uint8_t* payload, size_t total_len) {
  // BLE packets are made up of a 
  uint8_t len;
  uint8_t ad_type;
  uint8_t sizeConsumed = 0;
  Serial.print("Payload ");
  for (int i = 0; i < total_len; i++) {
    Serial.printf("%x|", payload[i]);
  }
  Serial.println("");

  while(true) {
    len = *payload;
    payload++; // Skip to type
    sizeConsumed += 1 + len;
    
    if (len == 0) {
      break; // A length of 0 indicates that we have reached the end.
    }
    
    ad_type = *payload;
    Serial.printf("section type %02x len %d\n", ad_type, len);
    switch(ad_type) {
      case TYPE_RACE:
        handleRocketActionMessage(payload);
        break;
      default:
        break;
    }
    payload += len;

    if (sizeConsumed >= total_len) {
      break;
    }
  }
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice d) {
      if (!d.getAddress().equals(match)) {
        return;
      }
      Serial.printf("Advertised Device: %s \n", d.toString().c_str());
      parseAdvertisement(d.getPayload(), d.getPayloadLength());
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(false); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}
