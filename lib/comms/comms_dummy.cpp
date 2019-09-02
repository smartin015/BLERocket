// dummy comms implementation
#ifdef COMMS_DUMMY
#include "comms_dummy.h"

CommsDummy::CommsDummy() {}

CommsDummy::~CommsDummy() {}

void CommsDummy::sendBytes(const adv_packet_t& p, const bool& retryUntilAck) {}

int CommsDummy::receiveToBuffer() {}

#endif // COMMS_DUMMY
