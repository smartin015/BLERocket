#ifndef ENGINE_H
#define ENGINE_H

#include "nav.h"
#include "comms_base.h"
#include <stdint.h>
#include <vector>
#include <limits>
#include <deque>
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

// We should ensure users can't surpass a certain score for the first
// half of the game.
#define MAX_SCORE std::numeric_limits<uint16_t>::max()
#define MAX_REPUTATION std::numeric_limits<uint16_t>::max()
#define PART_MAX_QUALITY std::numeric_limits<uint8_t>::max()
#define PART_MIN_QUALITY ((uint8_t) 1)

#define MAX_SHIP_NAME_LEN 8

// Get a sequence of button presses used to identify a particular user
#define USER_CODE_LEN 3
std::vector<nav::Command> getUserButtonSequence(uint8_t user_id);
std::string userButtonSequenceStr(const std::vector<nav::Command>& seq);

// Various ship helper methods
int getShipLaunchScore(const game::ShipT& ship);
std::string generateShipName(const game::ShipT& ship);

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
  game::ShipPartT getUserPart() const;
  int getSelectedShipIdx() const;
  int getCharIdx() const;
private:
  // Persisted game state
  game::StateT state;

  // Immutable (environment) state
  meta::DataT data;

  // Ephemeral state for trades
  std::deque<nav::Command> codeBuffer;
  std::vector<std::pair<time_t, game::ShipPartT>> localParts;
  time_t lastTradeAnnounce;
  void tradeLoop(CommsBase* comms);
  void tradeInput(const nav::Command& cmd, CommsBase* comms);
  void tradeMakePart(const game::ShipPartT& part);

  // Ephemeral state for selectors
  int selectedShip;
  int charIdx;

  // Ephemeral state for notifications/alerts
  std::vector<message::MessageT> messages;
  message::MessageT notification;
  bool notifyAcked;
};

#endif // ENGINE_H
