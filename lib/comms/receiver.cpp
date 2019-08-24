#include "msg.h"
#include <cstdint>

// int scanTime = 5; //In seconds
// BLEScan* pBLEScan;

// void handleShipActionMessage(uint8_t* ptr) {
//   char d[5];
//   ship_action_msg_t result;
//   memcpy(&result, ptr, sizeof(ship_action_msg_t));
// //  Serial.printf("Got ship action, msg %02x cargo %d speed %d c %d d %d dest %02x\n",
// //    result.msg,
// //    result.ship.cargo,
// //    result.ship.spd,
// //    result.ship.c,
// //    result.ship.d,
// //    result.dest);
// }

// void handlePartActionMessage(uint8_t* ptr) {
//   char d[5];
//   part_action_msg_t result;
//   memcpy(&result, ptr, sizeof(part_action_msg_t));
// //  Serial.printf("Got [art action, msg %02x part %s quality %d dest %02x\n",
// //    result.msg,
// //    PART_NAMES[result.part],
// //    result.quality,
// //    result.dest);
// }

// void parseAdvertisement(uint8_t* payload, size_t total_len) {
//   // BLE packets are made up of a
//   uint8_t len;
//   uint8_t ad_type;
//   uint8_t sizeConsumed = 0;
//   Serial.print("Recv ");
//   for (int i = 0; i < total_len; i++) {
//     Serial.printf("%x|", payload[i]);
//   }
//   Serial.println("");

//   while(true) {
//     len = *payload;
//     payload++; // Skip to type
//     sizeConsumed += 1 + len;

//     if (len == 0) {
//       break; // A length of 0 indicates that we have reached the end.
//     }

//     ad_type = *payload;
//     // Serial.printf("section type %02x len %d\n", ad_type, len);
//     switch(ad_type) {
//       case TYPE_TRADE:
//       case TYPE_EXPLORE:
//       case TYPE_RACE:
//         handleShipActionMessage(payload);
//         break;
//       case TYPE_GIVE:
//         handlePartActionMessage(payload);
//         break;
//       default:
//         Serial.printf("Unknown advertisement, type %02x\n", ad_type);
//         break;
//     }
//     payload += len;

//     if (sizeConsumed >= total_len) {
//       break;
//     }
//   }
// }

// BLEAddress match1("24:0a:c4:9a:a5:de");
// BLEAddress match2("24:0a:c4:9a:a6:ce");
// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//     void onResult(BLEAdvertisedDevice d) {
//       if (!d.getAddress().equals(match1) && !d.getAddress().equals(match2)) {
//         return;
//       }
//       parseAdvertisement(d.getPayload(), d.getPayloadLength());
//     }
// };

// bool scanning = false;
// void initReceiver() {
//   scanning = false;
//   pBLEScan = BLEDevice::getScan(); //create new scan
//   pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//   pBLEScan->setActiveScan(false); //active scan uses more power, but get results faster
//   pBLEScan->setInterval(100);
//   pBLEScan->setWindow(99);  // less or equal setInterval value
// }

// void scanComplete(BLEScanResults foundDevices) {
//   // Serial.printf("Found %d devices\n", foundDevices.getCount());
//   pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
//   scanning = false;
// }

// void doScan() {
//   if (scanning) {
//     return;
//   }
//   scanning = true;
//   pBLEScan->start(scanTime, &scanComplete, false);
// }
