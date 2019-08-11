
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
BLEAdvertising *pAdvertising;

void initSender() {
  pAdvertising = BLEDevice::getAdvertising();
}

// #define BEACON_PREAMBLE "54ACE" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
// BLEUUID uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";

void setTestMessage() {

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

void advertise() {
  pAdvertising->start();
  Serial.println("Advertising started...");
  delay(100);
  pAdvertising->stop();
}

void setRocketActionMessage(BLEAdvertisementData& adv, message_t msg, rocket_config_t rocket) {
  char d[5]; d[4] = 0;
  rocket_action_msg_t m;
  d[0] = sizeof(rocket_action_msg_t);
  m.msg = msg;
  m.rocket = rocket;
  memcpy(d+1, &m, sizeof(m));
  
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
