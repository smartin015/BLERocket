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
  page = nav::Page::MAIN;
  const auto& es = capnp::Schema::from<game::ShipPartType>().asEnum().getEnumerants();
  for (int i = 0; i < es.size(); i++) {
    game::ShipPartType t = (game::ShipPartType) es[i].getIndex();
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
  if (page == nav::Page::LAUNCH_ENTRY && cmd != nav::Command::LEFT) {
    for (const auto& kv : parts) {
      if (kv.second == 0) {
        return true;
      }
    }
  }
  return false;
}

void Engine::handleInput(const nav::Command& cmd) {
  switch (page) {
    case nav::Page::TRADE_ENTRY:
      if (cmd == nav::Command::UP) {
        // Test user action to "receive" a part (really just increment)
        // TODO: Handle user input code.
        parts[game::ShipPartType::HULL]++;
        parts[game::ShipPartType::THRUSTER]++;
        parts[game::ShipPartType::CARGO]++;
        parts[game::ShipPartType::SENSORS]++;
      }
      break;
    default:
      break;
  }

  if (suppressNav(cmd)) {
    return;
  }

  auto next = nextPage(page, cmd);
  if (next != nav::Page::NO_OP) {
    page = next;
  }
}

void Engine::handleMessage(const message::Message& msg) {
  std::cout << "TODO handle messages" << std::endl;
}
