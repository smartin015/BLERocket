#ifdef COMMS_BLE
#ifndef COMMS_BLE_H
#define COMMS_BLE_H

#include "comms_base.h"

class CommsBLE : public CommsBase {
public:
  CommsBLE();
  bool hasMessage();
  bool sendMessage(const message::Message& msg, bool retryUntilAck);
  const message::Message* receiveMessage();
private:
  // TODO
};


#endif // COMMS_BLE_H
#endif // COMMS_BLE
