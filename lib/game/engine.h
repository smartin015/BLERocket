#ifndef ENGINE_H
#define ENGINE_H

#include "nav.h"
#include "comms_base.h"
#include <stdint.h>
#include <vector>
#include "nav_generated.h"
#include "game_generated.h"
#include "message_generated.h"

class Engine {
public:
  Engine(const game::State* gameState);
  Engine() {};

  void handleInput(const nav::Command& cmd, CommsBase& comms);
  void handleMessage(const message::MessageT& msg);
  bool suppressNav(const nav::Command& cmd) const;
  nav::Page getPage() const;
  const game::StateT* getState() const;

private:
  game::StateT state;
};

#endif // ENGINE_H
