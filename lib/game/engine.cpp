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
  lastTradeAnnounce = TRADE_ANNOUNCE_OFF;
  lastStatus = 0;
  selectedShip = 0;
  mission = message::Type_race;
  charIdx = 0;
  codeBuffer.clear();

  // TODO remove
  if (state.status->score < PHASE2_SCORE_THRESHOLD) {
    ESP_LOGI(ENGINE_TAG, "Cheating to phase 2");
    state.status->score = PHASE2_SCORE_THRESHOLD;
    state.status->phase_id = 2;
  }
}

const game::StateT* Engine::getState() const {
  return &state;
};

nav::Page Engine::getPage() const {
  return state.page;
}

const std::vector<std::pair<time_t, game::StatusT>>* Engine::getNearbyClientStatuses() const {
  return &localStatus;
}

bool Engine::suppressNav(const nav::Command& cmd) const {
  // Suppress non-back action on launch page if not enough parts.
  if (state.page == nav::Page_launchEntry && cmd != nav::Command_left) {
    if (state.parts.size() < game::ShipPartType_MAX) {
      return true;
    }
  }

  // Don't allow viewing details on invalid selection state (e.g. no ships, bad index)
  if (nextPage(state.page, cmd) == nav::Page_shipDetails) {
    if (state.ships.size() == 0 || selectedShip < 0 || selectedShip >= state.ships.size()) {
      return true;
    }
  }

  // Suppress phase-2 actions if in phase 1
  if (state.status->phase_id != 2) {
    if (nextPage(state.page, cmd) == nav::Page_shipMissionSelect) {
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

void Engine::loop(CommsBase* comms) {
  tradeLoop(comms);
  statusLoop(comms);
}

int Engine::getSelectedShipIdx() const {
  return selectedShip;
}

int Engine::getCharIdx() const {
  return charIdx;
}

message::Type Engine::getMission() const {
  return mission;
}

void Engine::handleInput(const nav::Command& cmd, CommsBase* comms) {
  // Nav is handled *before* potentially state-modifying actions
  if (suppressNav(cmd)) {
    return;
  }
  auto next = nextPage(state.page, cmd);

  switch (state.page) {
    case nav::Page_tradeEntry:
      tradeInput(cmd, comms);
      break;
    case nav::Page_fleetEntry:
      if (cmd == nav::Command_up) {
        selectedShip = (selectedShip - 1 + state.ships.size()) % state.ships.size();
      } else if (cmd == nav::Command_down) {
        selectedShip = (selectedShip + 1) % state.ships.size();
      }
      break;
    case nav::Page_shipMissionSelect:
      switch (cmd) {
        case nav::Command_up:
          mission = (message::Type) std::max(mission - 1, (int) message::Type_race);
          break;
        case nav::Command_down:
          mission = (message::Type) std::min(mission + 1, (int) message::Type_explore);
          break;
        default:
          break;
      }
      break;
    case nav::Page_shipRename:
      switch (cmd) {
        case nav::Command_up:
          state.ships[selectedShip]->name[charIdx]++;
          break;
        case nav::Command_down:
          state.ships[selectedShip]->name[charIdx]--;
          break;
        case nav::Command_left:
          charIdx = std::max(0, charIdx-1);
          break;
        case nav::Command_right:
          charIdx = std::min(MAX_SHIP_NAME_LEN-1, charIdx+1);
          break;
        default:
          break;
      }
      break;
    case nav::Page_settingsReset:
      if (cmd == nav::Command_enter) {
        // Clear persistent and ephemeral state
        state = game::StateT();
        state.status.reset(new game::StatusT());
        notifyAcked = true;
        lastTradeAnnounce = TRADE_ANNOUNCE_OFF;
        selectedShip = 0;
        charIdx = 0;
        codeBuffer.clear();
      }
      break;
    case nav::Page_settingsSelectUser:
      switch (cmd) {
        case nav::Command_up:
          state.status->user = (state.status->user-1 + data.users.size()) % data.users.size();
          break;
        case nav::Command_down:
          state.status->user = (state.status->user+1) % data.users.size();
          break;
        default:
          break;
      }
      break;
    case nav::Page_launchEntry:
      if (cmd != nav::Command_left && !suppressNav(cmd)) {
        // Launching a new rocket - add it to the list of ships
        auto ship = std::unique_ptr<game::ShipT>(new game::ShipT());
        for (const auto& p : state.parts) {
          ship->parts.emplace_back(std::unique_ptr<game::ShipPartT>(new game::ShipPartT(*p)));
        }
        ship->owner = 2; // TODO
        ship->name = generateShipName(*ship);
        int score = getShipLaunchScore(*ship);
        state.status->score += score;
        state.ships.emplace_back(std::move(ship));

        ESP_LOGI(ENGINE_TAG, "New ship created! Score +%d (total %d)", score, state.status->score);

        // Select the new ship in future menus
        selectedShip = state.ships.size()-1;

        // Get rid of built up parts
        state.parts.clear();

        // If we're above a certain point threshold, enable phase 2
        if (state.status->phase_id < 2 && state.status->score >= PHASE2_SCORE_THRESHOLD) {
          state.status->phase_id = 2;
          state.status->phase_txn++;
        }

      }
    case nav::Page_settingsEntry:
      if (cmd == nav::Command_down) {
        sendTestStatus(comms);
      } else if (cmd == nav::Command_right) {
        sendTestShip(comms);
      }
      break;
    default:
      break;
  }

  if (next != nav::Page_noOp) {
    ESP_LOGI(ENGINE_TAG, "Nav to page %s", nav::EnumNamePage(next));
    state.page = next;
  }
}

void Engine::handleMessage(const message::MessageT& msg) {
  switch (msg.oneof.type) {
    case message::UMessage_status:
      handleStatus(*(msg.oneof.Asstatus()));
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
