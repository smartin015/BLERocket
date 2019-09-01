// Comms implementation using BLE
#ifdef COMMS_BLE
#include "comms_ble.h"
#include <Arduino.h>

BLEAddress match1("24:0a:c4:9a:a5:de");
BLEAddress match2("24:0a:c4:9a:a6:ce");
void CommsBLE::onResult(BLEAdvertisedDevice d) {
  if (!d.getAddress().equals(match1) && !d.getAddress().equals(match2)) {
    return;
  }
  parseAdvertisement(d.getPayload(), d.getPayloadLength());
}

CommsBLE::CommsBLE() {
  BLEDevice::init(BEACON_NAME);
  Serial.println(BLEDevice::getAddress().toString().c_str());

  pAdvertising = BLEDevice::getAdvertising();

  // Init receiver
  scanning = false;
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(this);
  pBLEScan->setActiveScan(false); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

CommsBLE::~CommsBLE() {
  // TODO
}

void CommsBLE::sendBytes(const adv_packet_t& p, const bool& retryUntilAck) {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  //setShipActionMessage(oAdvertisementData, TYPE_RACE, testShip, dest);
  // char d[sizeof(ship_action_msg_t) + 2];

  // d[0] = sizeof(ship_action_msg_t);
  // d[sizeof(ship_action_msg_t)+1] = 0;

  // ship_action_msg_t m;
  // m.msg = msg;
  // m.ship = ship;
  // m.dest = dest;
  // memcpy(d+1, &m, sizeof(m));

  // Serial.print("Msg ");
  // for (int i = 0; i < sizeof(ship_action_msg_t) + 2; i++) {
  //   Serial.printf("%02x|", d[i]);
  // }
  // Serial.println("");
  // adv.addData(d);

  // Max 31 bytes
  // std::string payload = oAdvertisementData.getPayload();
  // Serial.print("Payload ");
  // for (int i = 0; i < payload.size(); i++) {
  //   Serial.printf("%02x|", payload[i]);
  // }
  // Serial.println("");
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);

  // TODO
  // advertise_start = millis();
  // pAdvertising->start();
}

void CommsBLE::loop() {

  // TODO  pAdvertising->stop();

  // TODO periodically start scan
  // if (scanning) {
  //   return;
  // }
  // scanning = true;
  // pBLEScan->start(SCAN_TIME, &scanComplete, false);
}

int CommsBLE::receiveToBuffer() {
  // TODO
}

void CommsBLE::parseAdvertisement(uint8_t* payload, size_t total_len) {
  // BLE packets are made up of a
  uint8_t len;
  uint8_t ad_type;
  uint8_t sizeConsumed = 0;
  Serial.print("Recv ");
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
    // Serial.printf("section type %02x len %d\n", ad_type, len);
    Serial.printf("Unknown advertisement, type %02x\n", ad_type);
    payload += len;

    if (sizeConsumed >= total_len) {
      break;
    }
  }
}

void CommsBLE::scanComplete(BLEScanResults foundDevices) {
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  scanning = false;
}

#endif // COMMS_BLE
