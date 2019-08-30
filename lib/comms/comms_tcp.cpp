// Comms implementation using TCP
#ifdef COMMS_TCP
#include "comms_tcp.h"
// #include "mqtt/client.h"
// #include "capnp/serialize.h"

CommsTCP::CommsTCP(std::string address, std::string topic, std::string client_id) {
  // client = mqtt::client(address, client_id);

  // mqtt::connect_options connOpts;
  // connOpts.set_keep_alive_interval(20);
  // connOpts.set_clean_session(true);
  // client.connect(connOpts);
}

void CommsTCP::loop() {
  // Nothing needed
}

void CommsTCP::sendMessage(const message::Message& msg, bool retryUntilAck) {
  // Just send the message (thanks MQTT!)
  // std::str s = capnp::KJ_STRINGIFY(msg);
  // auto qos = (retryUntilAck) ? 1 /* at least once */ : 0 /* at most once */;
  // client.publish(topic, s, s.size(), qos, false /* retain */);
}

const message::Message* CommsTCP::receiveMessage() {
  // TODO async poll socket
  // const auto* msg = client.try_consume_message();

  // if (msg == NULL) {
  //   return NULL;
  // }

  // // Try to convert to capnp
  // msg->get_payload();
  // capnp::StreamFdMessageReader reader()
  return NULL;
}

#endif // COMMS_TCP
