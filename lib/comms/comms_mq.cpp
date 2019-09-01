// Comms implementation using TCP
#ifdef COMMS_MQ
#include "comms_mq.h"
#include <errno.h>
#include <iostream>

CommsMQ::CommsMQ() {
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_PACKET_SIZE;
  attr.mq_curmsgs = 0;
  mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);
  if ((mqd_t)-1 == mq) {
    std::cerr << "Failed to open message queue: " << errno << " " << strerror(errno) << std::endl;
  }
}

CommsMQ::~CommsMQ() {
  mq_close(mq);
  mq_unlink(QUEUE_NAME);
}

void CommsMQ::sendBytes(const adv_packet_t& p, const bool& retryUntilAck) {
   if (mq_send(mq, p, MAX_PACKET_SIZE, 0) == -1) {
    std::cerr << "Send message: " << errno << " " << strerror(errno) << std::endl;
  }
}

int CommsMQ::receiveToBuffer() {
  return mq_receive(mq, buffer, MAX_PACKET_SIZE, NULL);
}

#endif // COMMS_MQ
