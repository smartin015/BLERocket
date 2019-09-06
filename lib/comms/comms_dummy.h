#ifdef COMMS_DUMMY
#ifndef COMMS_DUMMY_H
#define COMMS_DUMMY_H

#include "comms_base.h"

class CommsDummy : public CommsBase {
public:
  CommsDummy();
  ~CommsDummy();
  void loop() {};
  void init() {};
protected:
  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck);
  virtual int receiveToBuffer();
};


#endif // COMMS_DUMMY_H
#endif // COMMS_DUMMY

