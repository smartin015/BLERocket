#include "engine.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

Engine::Engine(const game::State* gameState, const meta::Data* metadata) {
  if (gameState != NULL) {
    gameState->UnPackTo(&state, NULL);
  }

  if (state.status == NULL) {
    state.status.reset(new game::StatusT());
  }

  if (metadata != NULL) {
    metadata->UnPackTo(&data, NULL);
  }
  notifyAcked = true;
  lastTradeAnnounce = 0;
  codeBuffer.clear();
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
    if (state.parts.size() < game::ShipPartType_MAX) {
      return true;
    }
  }
  return false;
}


game::ShipPartT Engine::getUserPart() const {
  game::ShipPartT part;
  part.creator = state.status->user;

  // We increase the user's part quality
  // based on their closeness to the Phase 1 max score
  float quality = (float(PART_MAX_QUALITY) / float(MAX_SCORE)) * (state.status->score);
  part.quality = std::max(PART_MIN_QUALITY, std::min(PART_MAX_QUALITY, (uint8_t) std::round(quality)));

  // We use a modulo of the user's ID to determine
  // what part they're able to make.
  // This ensures roughly equal distribution
  // of parts.
  part.type = (game::ShipPartType) (part.creator % (game::ShipPartType_MAX - game::ShipPartType_MIN) + 1);

  return part;
}

std::vector<nav::Command> getUserButtonSequence(uint8_t user_id) {
  // We essentially convert username to quaternary, reserving the "left"
  // command as a back button.
  std::vector<nav::Command> result;
  while (user_id > 0) {
    switch ((user_id % 4)) {
      case 0:
        result.push_back(nav::Command_down);
        break;
      case 1:
        result.push_back(nav::Command_up);
        break;
      case 2:
        result.push_back(nav::Command_right);
        break;
      case 3:
        result.push_back(nav::Command_enter);
        break;
    }
    user_id /= 4;
  }
  while (result.size() < USER_CODE_LEN) { // Flat structure for 64 possible ID combinations
    result.push_back(nav::Command_down);
  }
  return result;
};

std::string userButtonSequenceStr(const std::vector<nav::Command>& seq) {
  std::string result;
  for (int i = 0; i < seq.size(); i++) {
    switch (seq[i]) {
      case nav::Command_down:
        result += "v";
        break;
      case nav::Command_up:
        result += "^";
        break;
      case nav::Command_right:
        result += ">";
        break;
      case nav::Command_enter:
        result += "X";
        break;
    }
  }
  return result;
}

void sendTestStatus(CommsBase* comms) {
  // Send example status message
  message::MessageT msg;
  msg.oneof.Set<game::StatusT>(game::StatusT());
  auto* stat = msg.oneof.Asstatus();
  stat->firmwareVersion = 5;
  stat->user = 123;
  stat->phase_id = 1;
  stat->phase_txn = 3;
  comms->sendMessage(msg, false);
}

void sendTestShip(CommsBase* comms) {
  // Send example ship message
  message::MessageT msg;
  msg.oneof.Set<message::ShipT>(message::ShipT());
  auto* s = msg.oneof.Asship();
  s->action = message::Type_give;
  s->dest_user = 1;
  s->ship.reset(new game::ShipT());
  s->ship->owner = 2;
  comms->sendMessage(msg, false);
}

void sendTestPart(CommsBase* comms) {
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

void Engine::loop(CommsBase* comms) {
  tradeLoop(comms);
}

void Engine::handleInput(const nav::Command& cmd, CommsBase* comms) {
  switch (state.page) {
    case nav::Page_tradeEntry:
      tradeInput(cmd, comms);
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
    case nav::Page_settingsEntry:
      if (cmd == nav::Command_down) {
        sendTestStatus(comms);
      } else if (cmd == nav::Command_right) {
        sendTestShip(comms);
      } else if (cmd == nav::Command_left) {
        sendTestPart(comms);
      }
      break;
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
        ESP_LOGI(ENGINE_TAG, "Ship: Action %s Name %s Parts TODO Owner %d Dest %d",
          message::EnumNameType(m->action),
          m->ship->name.c_str(),
          uint16_t(m->ship->owner),
          uint16_t(m->dest_user));

        notification.oneof.Set<message::ShipT>(message::ShipT());
        auto s = notification.oneof.Asship();
        s->action = message::Type_launch;
        s->dest_user = 0;
        s->ship.reset(new game::ShipT());
        s->ship->name = "aship";
        notifyAcked = false;
        ESP_LOGI(ENGINE_TAG, "Set notification");
      }
      break;
    case message::UMessage_part:
      {
        auto m = msg.oneof.Aspart();
        ESP_LOGI(ENGINE_TAG, "Part: Action %s Part %s Quality %d Dest %d Creator %d",
          message::EnumNameType(m->action),
          game::EnumNameShipPartType(m->part->type),
          uint16_t(m->part->quality),
          uint16_t(m->dest_user),
          uint16_t(m->part->creator));
        if (m->action == message::Type_make) {
          tradeMakePart(*(m->part));
        }
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
