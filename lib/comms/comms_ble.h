#ifdef COMMS_BLE
#ifndef COMMS_BLE_H
#define COMMS_BLE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "comms_base.h"

#define BEACON_NAME "ROCKETSNAT"
#define SCAN_TIME 5 // Seconds

class CommsBLE : public CommsBase, public BLEAdvertisedDeviceCallbacks {
public:
  CommsBLE();
  ~CommsBLE();
  void loop();
  void onResult(BLEAdvertisedDevice d);
protected:
  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck);
  virtual int receiveToBuffer();
private:
  bool scanning;
  BLEAdvertising *pAdvertising;
  BLEScan* pBLEScan;

  void parseAdvertisement(uint8_t* payload, size_t total_len);
  void scanComplete(BLEScanResults foundDevices);
};

#endif // COMMS_BLE_H
#endif // COMMS_BLE
