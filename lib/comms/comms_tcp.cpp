// Comms implementation using TCP
#ifdef COMMS_TCP
#include "comms_tcp.h"

CommsTCP::CommsTCP() {
  // TODO setup TCP connection to port
}

void CommsTCP::loop() {
  // Nothing needed
}

void CommsTCP::sendMessage(const message::Message& msg, bool retryUntilAck) {
  // TODO just send the message (thanks TCP)
}

const message::Message* CommsTCP::receiveMessage() {
  // TODO async poll socket
  return NULL;
}

#endif // COMMS_TCP
