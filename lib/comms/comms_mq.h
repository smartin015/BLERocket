#ifdef COMMS_MQ
#ifndef COMMS_MQ_H
#define COMMS_MQ_H

#include <mqueue.h>
#include "comms_base.h"

#define QUEUE_NAME  "/rockets-n-at"

class CommsMQ : public CommsBase {
public:
  CommsMQ();
  ~CommsMQ();
  void loop() {};
protected:
  virtual void sendBytes(const adv_packet_t& p, const bool& retryUntilAck);
  virtual int receiveToBuffer();
private:
  struct mq_attr attr;
  mqd_t mq;
};


#endif // COMMS_MQ_H
#endif // COMMS_MQ
