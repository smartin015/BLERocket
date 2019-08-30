#ifndef COMMS_BASE_H
#define COMMS_BASE_H

#include "message_generated.h"

class CommsBase {
public:
  // Maintain the connection to other devices.
  // Subsequent calls to loop() may clear any queued messages
  void loop() {}

  void sendMessage(const message::Message& msg, bool retryUntilAck) {};

  const message::Message* receiveMessage() {return NULL;};
};

#endif // COMMS_BASE_H
