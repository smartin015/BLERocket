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
#include "ship.h"

#ifdef ARDUINO_LOLIN_D32_PRO
#include "esp_log.h"
#else
#include "macrologger.h"
#endif

#define ENGINE_TAG "engine"
#define STATUS_INTERVAL_SECS 60
#define TRADE_ANNOUNCE_SECS 10
#define STATUS_ANNOUNCE_SECS 20
#define TRADE_ANNOUNCE_OFF std::numeric_limits<time_t>::max()
#define LOCAL_PART_TIMEOUT_SECS 60
#define LOCAL_STATUS_TIMEOUT_SECS 60

// We should ensure users can't surpass a certain score for the first
// half of the game.
#define MAX_SCORE std::numeric_limits<uint16_t>::max()
#define MAX_REPUTATION std::numeric_limits<uint16_t>::max()
#define PHASE2_SCORE_THRESHOLD 10000
#define PART_MAX_QUALITY std::numeric_limits<uint8_t>::max()
#define PART_MIN_QUALITY ((uint8_t) 1)

// Get a sequence of button presses used to identify a particular user
#define USER_CODE_LEN 3
std::vector<nav::Command> getUserButtonSequence(uint8_t user_id);
std::string userButtonSequenceStr(const std::vector<nav::Command>& seq);

typedef struct trade_state_t {
  std::deque<nav::Command> codeBuffer;
  std::vector<std::pair<time_t, game::ShipPartT>> localParts;
  time_t lastAnnounce;
} trade_state_t;

typedef struct mission_state_t {
  std::vector<std::pair<time_t, game::StatusT>> localStatus;
  std::vector<std::pair<time_t, std::string>> activeShips;
  time_t lastStatus;
  message::Type type;
} mission_state_t;

typedef struct event_state_t {
  message::MessageT message;
  time_t lastMessage;
  bool acked;
  // For ship responses
  const meta::ScenarioT* scenario;
  int selectedChoice;
  uint8_t d20;
} event_state_t;

class Engine {
public:
  Engine(const game::State* gameState, const meta::Data* metadata);
  Engine() {};

  // Input handling functions
  void handleInput(const nav::Command& cmd, CommsBase* comms);
  void handleMessage(const message::MessageT& msg);
  void ackEvent();

  // Loop calls several sub-loops to handle non-input updates
  void loop(CommsBase* comms);

  // Getters for UI
  bool suppressNav(const nav::Command& cmd) const;
  nav::Page getPage() const;
  const game::StateT* getState() const;
  const meta::DataT* getData() const;
  const event_state_t* getEvent() const;
  const mission_state_t* getMission() const;
private:
  game::StateT state; // Persisted game state
  meta::DataT data; // Immutable (environment) state

  void clearVolatileState();
  void tradeLoop(CommsBase* comms);
  void tradeInput(const nav::Command& cmd, CommsBase* comms);
  void tradeMakePart(const game::ShipPartT& part);
  void tradePartBroadcast(CommsBase* comms, const game::ShipPartT& part);
  trade_state_t trade;
  void missionLoop(CommsBase* comms);
  void missionHandleStatus(const game::StatusT& status);
  void missionUpdateScoreAndRep();
  mission_state_t mission;
  event_state_t event;

};

#endif // ENGINE_H
