#include "game.h"
#include "msg.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
BLEAdvertising *pAdvertising;

void initSender() {
  pAdvertising = BLEDevice::getAdvertising();
}

// #define BEACON_PREAMBLE "54ACE" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
// BLEUUID uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";

void setTestMessage() {

  ship_t testShip;
//  testShip.cargo = 2;
//  testShip.spd = 2;
//  testShip.c = 3;
//  testShip.d = 1;

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  user_t dest;
  setShipActionMessage(oAdvertisementData, TYPE_RACE, testShip, dest);

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

void advertise() {
  pAdvertising->start();
  delay(100);
  pAdvertising->stop();
  Serial.println("Advertised");
}

void setShipActionMessage(BLEAdvertisementData& adv, message_t msg, ship_t ship, user_t dest) {
  char d[sizeof(ship_action_msg_t) + 2];

  d[0] = sizeof(ship_action_msg_t);
  d[sizeof(ship_action_msg_t)+1] = 0;

  ship_action_msg_t m;
  m.msg = msg;
  m.ship = ship;
  m.dest = dest;
  memcpy(d+1, &m, sizeof(m));

  Serial.print("Msg ");
  for (int i = 0; i < sizeof(ship_action_msg_t) + 2; i++) {
    Serial.printf("%02x|", d[i]);
  }
  Serial.println("");
  adv.addData(d);
}

void setPartActionMessage(BLEAdvertisementData& adv, message_t msg, ship_part_t part, uint8_t quality, user_t dest) {
  char d[sizeof(part_action_msg_t) + 2];
  d[0] = sizeof(part_action_msg_t);
  d[sizeof(part_action_msg_t)+1] = 0;

  part_action_msg_t m;
  m.msg = msg;
  m.part = part;
  m.quality = quality;
  m.dest = dest;
  memcpy(d+1, &m, sizeof(m));

  Serial.print("Msg ");
  for (int i = 0; i < sizeof(part_action_msg_t) + 2; i++) {
    Serial.printf("%02x|", d[i]);
  }
  Serial.println("");
  adv.addData(d);
}
