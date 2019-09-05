#include "engine.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

Engine::Engine(const game::State* gameState, const meta::Data* metadata) {
  if (gameState != NULL) {
    gameState->UnPackTo(&state, NULL);
  } else {
    state.status.reset();
  }
  if (metadata != NULL) {
    metadata->UnPackTo(&data, NULL);
  }
  notifyAcked = true;
}

const game::StateT* Engine::getState() const {
  return &state;
};

nav::Page Engine::getPage() const {
  return state.page;
}

bool Engine::suppressNav(const nav::Command& cmd) const {
  // Suppress non-back action on launch page if not enough parts.
  if (state.page == nav::Page_launchEntry && cmd != nav::Command_left) {
    for (const auto& p : state.parts) {
      if (p->quality == 0) {
        return true;
      }
    }
  }
  return false;
}

void Engine::handleInput(const nav::Command& cmd, CommsBase* comms) {
  switch (state.page) {
    case nav::Page_tradeEntry:
      if (cmd == nav::Command_up) {
        // Test user action to "receive" a part (really just increment)
        // TODO: Handle user input code.
        if (state.parts.size() == 0) {
          for (int i = game::ShipPartType_MIN; i <= game::ShipPartType_MAX; i++) {
            auto part = std::unique_ptr<game::ShipPartT>(new game::ShipPartT());
            part->type = (game::ShipPartType) i;
            part->quality = 1;
            part->creator = 2; // TODO
            state.parts.emplace_back(std::move(part));
          }
        }
      } else if (cmd == nav::Command_down) {
        // Send example status message
        message::MessageT msg;
        msg.oneof.Set<game::StatusT>(game::StatusT());
        auto* stat = msg.oneof.Asstatus();
        stat->firmwareVersion = 5;
        stat->user = 123;
        stat->phase_id = 1;
        stat->phase_txn = 3;
        comms->sendMessage(msg, false);
      } else if (cmd == nav::Command_right) {
        // Send example ship message
        message::MessageT msg;
        msg.oneof.Set<message::ShipT>(message::ShipT());
        auto* s = msg.oneof.Asship();
        s->action = message::Type_give;
        s->dest_user = 1;
        s->ship.reset(new game::ShipT());
        s->ship->owner = 2;
        comms->sendMessage(msg, false);
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
        comms->sendMessage(msg, false);
      }
      break;
    case nav::Page_launchEntry:
      if (cmd != nav::Command_left && !suppressNav(cmd)) {
        // Launching a new rocket - add it to the list of ships
        auto ship = std::unique_ptr<game::ShipT>(new game::ShipT());
        ship->name = "aship";
        for (const auto& p : state.parts) {
          ship->parts.emplace_back(std::unique_ptr<game::ShipPartT>(new game::ShipPartT(*p)));
        }
        ship->owner = 2; // TODO
        state.ships.emplace_back(std::move(ship));
        ESP_LOGI(ENGINE_TAG, "New ship created");

        // Get rid of built up parts
        state.parts.clear();
      }
    default:
      break;
  }

  if (suppressNav(cmd)) {
    return;
  }

  auto next = nextPage(state.page, cmd);
  if (next != nav::Page_noOp) {
    ESP_LOGI(ENGINE_TAG, "Nav to page %s", nav::EnumNamePage(next));
    state.page = next;
  }
}

void Engine::handleMessage(const message::MessageT& msg) {
  switch (msg.oneof.type) {
    case message::UMessage_status:
      {
        auto m = msg.oneof.Asstatus();
        ESP_LOGI(ENGINE_TAG, "Status: FirmwareVersion %d Site %d Score %d Rep %d User %d Phase %d (tx %d)",
         uint16_t(m->firmwareVersion),
         uint16_t(m->site),
         m->score,
         m->reputation,
         uint16_t(m->user),
         uint16_t(m->phase_id),
         uint16_t(m->phase_txn));
      }
      break;
    case message::UMessage_ship:
      {
        auto m = msg.oneof.Asship();
        std::cout << "Ship: \n"
          << "action " << message::EnumNameType(m->action) << "\n"
          << "destination " << uint16_t(m->dest_user) << "\n"
          //<< "name " << m->ship->name << "\n"
          //<< "owner " << uint16_t(m->ship->owner) << "\n";
          << "parts TODO" << "\n"
          << "creators TODO" << "\n";

        notification.oneof.Set<message::ShipT>(message::ShipT());
        auto s = notification.oneof.Asship();
        s->action = message::Type_launch;
        s->dest_user = 0;
        s->ship.reset(new game::ShipT());
        s->ship->name = "aship";
        notifyAcked = false;
        std::cout << "Set notification" << std::endl;
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

const meta::DataT* Engine::getData() const {
  return &data;
}

const message::MessageT* Engine::getNotification() const {
  if (notifyAcked) {
    return NULL;
  }
  return &notification;
}

void Engine::ackNotification() {
  notifyAcked = true;
}

const message::MessageT* Engine::peekMessage() const {
  if (messages.size() == 0) {
    return NULL;
  }
  return &(messages[0]);
}

void Engine::ackMessage() {
  if (messages.size() == 0) {
    return;
  }
  messages.erase(messages.begin());
}
