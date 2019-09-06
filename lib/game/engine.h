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

#ifdef ARDUINO_LOLIN_D32_PRO
#include "esp_log.h"
#else
#include "macrologger.h"
#endif

#define ENGINE_TAG "engine"
#define STATUS_INTERVAL_SECS 60
#define TRADE_ANNOUNCE_SECS 60
#define LOCAL_PART_TIMEOUT_SECS 120

class Engine {
public:
  Engine(const game::State* gameState, const meta::Data* metadata);
  Engine() {};

  void handleInput(const nav::Command& cmd, CommsBase* comms);
  void handleMessage(const message::MessageT& msg);
  void loop(CommsBase* comms);
  bool suppressNav(const nav::Command& cmd) const;
  nav::Page getPage() const;
  const game::StateT* getState() const;
  const meta::DataT* getData() const;
  const message::MessageT* getNotification() const;
  void ackNotification();
  const message::MessageT* peekMessage() const;
  void ackMessage();
private:
  // Persisted game state
  game::StateT state;

  // Immutable (environment) state
  meta::DataT data;

  // Ephemeral state for trades
  std::vector<std::pair<time_t, game::ShipPartT>> localParts;
  time_t lastTradeAnnounce;
  void tradeLoop(CommsBase* comms);
  void tradeInput(const nav::Command& cmd, CommsBase* comms);
  void tradeMakePart(const game::ShipPartT& part);

  // Ephemeral state for notifications/alerts
  std::vector<message::MessageT> messages;
  message::MessageT notification;
  bool notifyAcked;
};

#endif // ENGINE_H
