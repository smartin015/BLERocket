#ifdef COMMS_MQ
#ifndef COMMS_MQ_H
#define COMMS_MQ_H

#include <mqueue.h>
#include "comms_base.h"

#define QUEUE_NAME  "/rocketsnat"

class CommsMQ : public CommsBase {
public:
  CommsMQ();
  ~CommsMQ();
  void loop() {};
protected:
  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck);
  virtual int receiveToBuffer();
private:
  mqd_t mq;
};


#endif // COMMS_MQ_H
#endif // COMMS_MQ
