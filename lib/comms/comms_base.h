#ifndef COMMS_BASE_H
#define COMMS_BASE_H

#include "message_generated.h"
#include <memory>
#include <iostream>

// This packet ID prefixes every game packet
#define PACKET_ID 0x7A

// BLE advertisement max payload size is 31 bytes,
// but we limit to 30 to allow for a common ID at the head of every packet.
#define MAX_PACKET_SIZE    30
typedef char adv_packet_t[MAX_PACKET_SIZE+1];

class CommsBase {
public:
  // Maintain the connection to other devices.
  // Subsequent calls to loop() may clear any queued messages
  virtual void loop() = 0;

  void sendMessage(const message::MessageT& msg, const bool& retryUntilAck);

  const message::MessageT receiveMessage();

protected:
  void packMessage(const message::MessageT& msg, adv_packet_t& p);
  const message::MessageT unpackMessage(const adv_packet_t& p);

  adv_packet_t buffer;

  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck) = 0;
  virtual int receiveToBuffer() = 0;
};

#endif // COMMS_BASE_H
