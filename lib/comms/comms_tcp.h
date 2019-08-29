#ifdef COMMS_TCP
#ifndef COMMS_TCP_H
#define COMMS_TCP_H

#include "comms_base.h"

class CommsTCP : public CommsBase {
public:
  CommsTCP();
  void loop();
  void sendMessage(const message::Message& msg, bool retryUntilAck);
  const message::Message* receiveMessage();
private:
  // TODO
};


#endif // COMMS_TCP_H
#endif // COMMS_TCP
