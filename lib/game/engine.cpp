#include "engine.h"

#include <iostream>
#include <string.h>
#include <capnp/schema.h>
#include <stdlib.h>

template <class T> std::string enumStr(T e) {
  auto x = capnp::Schema::from<T>();
  return x.asEnum().getEnumerants()[(int)e].getProto().getName().cStr();
}

Engine::Engine() {
  page = nav::Page_main;
  const auto& es = game::EnumValuesShipPartType();
  for (int i = game::ShipPartType_MIN; i <= game::ShipPartType_MAX; i++) {
    game::ShipPartType t = es[i];
    parts[t] = 0;
  }
}

nav::Page Engine::getPage() const {
  return page;
}

const std::map<game::ShipPartType, uint8_t> Engine::getParts() const {
  return parts;
}

bool Engine::suppressNav(const nav::Command& cmd) const {
  // Suppress non-back action on launch page if not enough parts.
  if (page == nav::Page_launchEntry && cmd != nav::Command_left) {
    for (const auto& kv : parts) {
      if (kv.second == 0) {
        return true;
      }
    }
  }
  return false;
}

void Engine::handleInput(const nav::Command& cmd, CommsBase comms) {
  switch (page) {
    case nav::Page_tradeEntry:
      if (cmd == nav::Command_up) {
        // Test user action to "receive" a part (really just increment)
        // TODO: Handle user input code.
        parts[game::ShipPartType_hull]++;
        parts[game::ShipPartType_thruster]++;
        parts[game::ShipPartType_cargo]++;
        parts[game::ShipPartType_sensors]++;
      }
      break;
    default:
      break;
  }

  if (suppressNav(cmd)) {
    return;
  }

  auto next = nextPage(page, cmd);
  if (next != nav::Page_noOp) {
    page = next;
  }
}

void Engine::handleMessage(const message::Message& msg) {
  std::cout << "TODO handle messages" << std::endl;
}
