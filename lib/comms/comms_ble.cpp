// Comms implementation using BLE
#ifdef COMMS_BLE
#include "comms_ble.h"
#include <Arduino.h>
#include <functional>
using namespace std::placeholders;

static std::vector<adv_packet_t> stored_packets;

// BLEAddress match1("24:0a:c4:9a:a5:de");
// BLEAddress match2("24:0a:c4:9a:a6:ce");
void CommsBLE::onResult(BLEAdvertisedDevice d) {
  uint8_t* payload = d.getPayload();
  size_t total_len = d.getPayloadLength();

  uint8_t len;
  uint16_t ad_type;
  uint8_t msg_type;
  uint8_t sizeConsumed = 0;

  while(true) {
    len = *payload;
    payload++; // Skip to type
    sizeConsumed += 1 + len;

    if (len == 0) {
      break; // A length of 0 indicates that we have reached the end.
    }

    ad_type = ((*(payload+1)) << 8) | (*(payload) & 0xFF);
    msg_type = *(payload+2);
    if (ad_type == PACKET_ID
      && msg_type >= message::UMessage_MIN
      && msg_type <= message::UMessage_MAX) {
      ESP_LOGI(BLE_TAG, "packet id %x type %02x len %d", ad_type, msg_type, len);
      Serial.print("Recv ");
      stored_packets.push_back(adv_packet_t());
      for (int i = 0; i < std::min((int)len, MAX_PACKET_SIZE); i++) {
        stored_packets[stored_packets.size()-1][i] = payload[2+i];
        Serial.printf("%02x|", payload[i]);
      }
      Serial.println();
    } else {
      payload += len;
    }

    if (sizeConsumed >= total_len) {
      break;
    }
  }
}

void CommsBLE::init() {
  BLEDevice::init(BEACON_NAME);
  Serial.println(BLEDevice::getAddress().toString().c_str());

  pAdvertising = BLEDevice::getAdvertising();

  // Init receiver
  advertise_start = 0;
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(this);
  pBLEScan->setActiveScan(false); //active scan uses more power, but gets results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

CommsBLE::~CommsBLE() {
  // TODO
}

void CommsBLE::sendBytes(const adv_packet_t& p, const bool& retryUntilAck) {
  ESP_LOGI(BLE_TAG, "Sending bytes");
  oAdvertisementData = BLEAdvertisementData();
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04

  // Copy packet to BLE advertisement
  std::string d;
  d.resize(MAX_PACKET_SIZE+2);
  d[0] = MAX_PACKET_SIZE;
  d[1] = PACKET_ID & 0xFF;
  d[2] = (PACKET_ID >> 8) & 0XFF;
  for (int i = 0; i < MAX_PACKET_SIZE; i++) {
    d[i+3] = p.data()[i];
  }
  size_t size_pre = oAdvertisementData.getPayload().length();
  oAdvertisementData.addData(d);
  size_t size_post = oAdvertisementData.getPayload().length();
  if (size_pre == size_post) {
    ESP_LOGE(BLE_TAG, "Could not add message data to BLE advertisement! Too large?");
    return;
  }

  {
    std::string payload = oAdvertisementData.getPayload();
    ESP_LOGI(BLE_TAG, "Msg (%d)", (int) payload.length());
    for (int i = 0; i < payload.length(); i++) {
      Serial.printf("%02x|", payload[i]);
    }
    Serial.println("");
  }

  pAdvertising->setAdvertisementData(oAdvertisementData);

  // Empty scan response
  oScanResponseData = BLEAdvertisementData();
  pAdvertising->setScanResponseData(oScanResponseData);

  // Make the same messages visible locally (parity with MQ behavior)
  stored_packets.push_back(p);

  advertise_start = millis();
  ESP_LOGI(BLE_TAG, "Starting advertisement");
  pAdvertising->start();
}

void CommsBLE::loop() {
  // Wait required time before stopping advertisement.
  if (advertise_start != 0 && millis() > advertise_start + ADVERTISE_DURATION_MILLIS) {
    advertise_start = 0;
    pAdvertising->stop();
    ESP_LOGI(BLE_TAG, "Stopped advertisement");
  }

  if (advertise_start == 0 && millis() - scan_start > SCAN_INTERVAL_MILLIS) {
    pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
    pBLEScan->start(SCAN_TIME_SECONDS, NULL, false);
    scan_start = millis();
  }
}

int CommsBLE::receiveToBuffer() {
  if (stored_packets.size() == 0) {
    return 0;
  }
  memcpy(buffer.data(), &(stored_packets[0]), MAX_PACKET_SIZE);
  stored_packets.erase(stored_packets.begin());
  return MAX_PACKET_SIZE;
}

#endif // COMMS_BLE
