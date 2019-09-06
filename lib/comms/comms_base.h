#ifndef COMMS_BASE_H
#define COMMS_BASE_H

#include "message_generated.h"
#include <memory>
#include <iostream>

// This packet ID prefixes every game packet
#define PACKET_ID 0x6CC6

// BLE advertisement max payload size is 31 bytes,
// but we allow for a common ID at the head of every packet.
// This plus some other stuff brings us down to 26 usable bytes for data.
#define MAX_PACKET_SIZE    26
typedef std::array<char, MAX_PACKET_SIZE+1> adv_packet_t;

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
