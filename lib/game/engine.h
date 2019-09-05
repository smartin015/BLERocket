#ifndef ENGINE_H
#define ENGINE_H

#include "nav.h"
#include "comms_base.h"
#include <stdint.h>
#include <vector>
#include "nav_generated.h"
#include "game_generated.h"
#include "message_generated.h"
#include "meta_generated.h"
#include "esp_log.h"

#define ENGINE_TAG "engine"

class Engine {
public:
  Engine(const game::State* gameState, const meta::Data* metadata);
  Engine() {};

  void handleInput(const nav::Command& cmd, CommsBase* comms);
  void handleMessage(const message::MessageT& msg);
  bool suppressNav(const nav::Command& cmd) const;
  nav::Page getPage() const;
  const game::StateT* getState() const;
  const meta::DataT* getData() const;
  const message::MessageT* getNotification() const;
  void ackNotification();
  const message::MessageT* peekMessage() const;
  void ackMessage();
private:
  game::StateT state;
  meta::DataT data;
  std::vector<message::MessageT> messages;
  message::MessageT notification;
  bool notifyAcked;
};

#endif // ENGINE_H
