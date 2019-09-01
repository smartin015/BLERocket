#include "engine.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

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

void Engine::handleInput(const nav::Command& cmd, CommsBase& comms) {
  switch (page) {
    case nav::Page_tradeEntry:
      if (cmd == nav::Command_up) {
        // Test user action to "receive" a part (really just increment)
        // TODO: Handle user input code.
        parts[game::ShipPartType_hull]++;
        parts[game::ShipPartType_thruster]++;
        parts[game::ShipPartType_cargo]++;
        parts[game::ShipPartType_sensors]++;
      } else if (cmd == nav::Command_down) {
        // Send example status message
        message::MessageT msg;
        msg.oneof.Set<message::StatusT>(message::StatusT());
        auto* stat = msg.oneof.Asstatus();
        stat->firmwareVersion = 5;
        stat->user = 123;
        stat->phase_id = 1;
        stat->phase_txn = 3;
        comms.sendMessage(msg, false);
      } else if (cmd == nav::Command_right) {
        // Send example ship message
        message::MessageT msg;
        msg.oneof.Set<message::ShipT>(message::ShipT());
        auto* s = msg.oneof.Asship();
        s->action = message::Type_give;
        s->dest = 1;
        s->ship.reset(new game::ShipT());
        s->ship->owner = 2;
        comms.sendMessage(msg, false);
      } else if (cmd == nav::Command_left) {
        // Send example part message
        message::MessageT msg;
        msg.oneof.Set<message::PartT>(message::PartT());
        auto* s = msg.oneof.Aspart();
        s->action = message::Type_give;
        s->dest_user = 1;
        s->part.reset(new game::ShipPartT());
        s->part->type = game::ShipPartType_hull;
        s->part->quality = 5;
        comms.sendMessage(msg, false);
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

void Engine::handleMessage(const message::MessageT& msg) {
  switch (msg.oneof.type) {
    case message::UMessage_status:
      {
        auto m = msg.oneof.Asstatus();
        std::cout << "Status: \n"
          << "firmwareVersion " << uint16_t(m->firmwareVersion) << "\n"
          << "site " << uint16_t(m->site) << "\n"
          << "score " << m->score << "\n"
          << "reputation " << m->reputation << "\n"
          << "user " << uint16_t(m->user) << "\n"
          << "phase " << uint16_t(m->phase_id) << " (tx " << uint16_t(m->phase_txn) << ")" << std::endl;
      }
      break;
    case message::UMessage_ship:
      {
        auto m = msg.oneof.Asship();
        std::cout << "Ship: \n"
          << "action " << message::EnumNameType(m->action) << "\n"
          << "destination " << uint16_t(m->dest) << "\n"
          //<< "name " << m->ship->name << "\n"
          //<< "owner " << uint16_t(m->ship->owner) << "\n";
          << "parts TODO" << "\n"
          << "creators TODO" << "\n";
      }
      break;
    case message::UMessage_part:
      {
        auto m = msg.oneof.Aspart();
        std::cout << "Part: \n"
          << "action " << message::EnumNameType(m->action) << "\n"
          << "part " << game::EnumNameShipPartType(m->part->type) << "\n"
          << "quality " << uint16_t(m->part->quality) << "\n"
          << "destination " << uint16_t(m->dest_user) << std::endl;
      }
      break;
    default:
      std::cerr << "Unhandled message type " << message::EnumNameUMessage(msg.oneof.type) << std::endl;
  }
}
