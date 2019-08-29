// Comms implementation using BLE
#ifdef COMMS_BLE
#include "comms_ble.h"

// // See the following for generating UUIDs:
// // https://www.uuidgenerator.net/
// BLEAdvertising *pAdvertising;

// void initSender() {
//   pAdvertising = BLEDevice::getAdvertising();
// }

// // #define BEACON_PREAMBLE "54ACE" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
// // BLEUUID uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";

// void setTestMessage() {

//   ship_t testShip;
// //  testShip.cargo = 2;
// //  testShip.spd = 2;
// //  testShip.c = 3;
// //  testShip.d = 1;

//   BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
//   BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
//   oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
//   user_t dest;
//   setShipActionMessage(oAdvertisementData, TYPE_RACE, testShip, dest);

//   // Max 31 bytes
//   std::string payload = oAdvertisementData.getPayload();
//   Serial.print("Payload ");
//   for (int i = 0; i < payload.size(); i++) {
//     Serial.printf("%02x|", payload[i]);
//   }
//   Serial.println("");

//   pAdvertising->setAdvertisementData(oAdvertisementData);
//   pAdvertising->setScanResponseData(oScanResponseData);
// }

// void advertise() {
//   pAdvertising->start();
//   delay(100);
//   pAdvertising->stop();
//   Serial.println("Advertised");
// }

// void setShipActionMessage(BLEAdvertisementData& adv, message_t msg, ship_t ship, user_t dest) {
//   char d[sizeof(ship_action_msg_t) + 2];

//   d[0] = sizeof(ship_action_msg_t);
//   d[sizeof(ship_action_msg_t)+1] = 0;

//   ship_action_msg_t m;
//   m.msg = msg;
//   m.ship = ship;
//   m.dest = dest;
//   memcpy(d+1, &m, sizeof(m));

//   Serial.print("Msg ");
//   for (int i = 0; i < sizeof(ship_action_msg_t) + 2; i++) {
//     Serial.printf("%02x|", d[i]);
//   }
//   Serial.println("");
//   adv.addData(d);
// }

// void setPartActionMessage(BLEAdvertisementData& adv, message_t msg, ship_part_t part, uint8_t quality, user_t dest) {
//   char d[sizeof(part_action_msg_t) + 2];
//   d[0] = sizeof(part_action_msg_t);
//   d[sizeof(part_action_msg_t)+1] = 0;

//   part_action_msg_t m;
//   m.msg = msg;
//   m.part = part;
//   m.quality = quality;
//   m.dest = dest;
//   memcpy(d+1, &m, sizeof(m));

//   Serial.print("Msg ");
//   for (int i = 0; i < sizeof(part_action_msg_t) + 2; i++) {
//     Serial.printf("%02x|", d[i]);
//   }
//   Serial.println("");
//   adv.addData(d);
// }

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


#endif // COMMS_BLE
