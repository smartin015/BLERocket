#ifdef COMMS_BLE
#ifndef COMMS_BLE_H
#define COMMS_BLE_H

#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <queue>

#include "comms_base.h"

#define BLE_TAG "comms_ble"
#define ADVERTISE_DURATION_MILLIS 300
#define SCAN_INTERVAL_MILLIS 5000
#define BEACON_NAME "ROCKETSNAT"
#define SCAN_TIME_SECONDS 3 // Seconds

class CommsBLE : public CommsBase, public BLEAdvertisedDeviceCallbacks {
public:
  CommsBLE() {};
  ~CommsBLE();
  void init();
  void loop();
  void onResult(BLEAdvertisedDevice d);
protected:
  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck);
  virtual int receiveToBuffer();
private:
  uint64_t advertise_start;
  uint64_t scan_start;
  BLEAdvertising *pAdvertising;
  BLEAdvertisementData oAdvertisementData;
  BLEAdvertisementData oScanResponseData;
  BLEScan* pBLEScan;
  std::queue<adv_packet_t> stored_packets;
};

#endif // COMMS_BLE_H
#endif // COMMS_BLE
