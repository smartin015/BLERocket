#include "engine.h"

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
      default:
        break;
    }
  }
  return result;
}

void Engine::tradePartBroadcast(CommsBase* comms, const game::ShipPartT& part) {
  ESP_LOGI(ENGINE_TAG, "Announcing trade");
  message::MessageT msg;
  msg.source_user = state.status->user;
  msg.oneof.Set<message::PartT>(message::PartT());
  auto* s = msg.oneof.Aspart();
  s->action = message::Type_make;
  s->dest_user = 0; // 0 reaches all users
  s->part.reset(new game::ShipPartT(part)); // part generated based on current state
  comms->sendMessage(msg, false);
}

void Engine::tradeLoop(CommsBase* comms) {
  // Periodically announce trades
  time_t now = time(NULL);
  if (state.page == nav::Page_tradeEntry) {
    if (trade.lastAnnounce == TRADE_ANNOUNCE_OFF || trade.lastAnnounce + TRADE_ANNOUNCE_SECS < now) {
      ESP_LOGI(ENGINE_TAG, "Advertising trade");
      tradePartBroadcast(comms, generatePart(state.status->user, state.status->score));

      // Cheat, broadcasting other important parts
       game::ShipPartT p;
       p.quality = 2;
       p.creator = 3;
       p.type = game::ShipPartType_hull;
       tradePartBroadcast(comms, p);
       p.creator = 1;
       p.type = game::ShipPartType_thruster;
       tradePartBroadcast(comms, p);
       p.creator = 7;
       p.type = game::ShipPartType_cargo;
       tradePartBroadcast(comms, p);
       p.creator = 9;
       p.type = game::ShipPartType_sensors;
       tradePartBroadcast(comms, p);

      trade.lastAnnounce = now;
    }
  } else if (trade.lastAnnounce != 0) { // on-exit cleanup tasks
    trade.lastAnnounce = TRADE_ANNOUNCE_OFF;
    while (!trade.codeBuffer.empty()) {
      trade.codeBuffer.pop_front();
    }
  }
}

const trade_state_t* Engine::getTradeState() const {
  return &trade;
}

void Engine::tradeInput(const nav::Command& cmd, CommsBase* comms) {
  // Keep a rolling buffer of the last 3 buttons pressed
  trade.codeBuffer.push_back(cmd);
  if (trade.codeBuffer.size() > USER_CODE_LEN) {
    trade.codeBuffer.pop_front();
  }

  time_t now = time(NULL);
  for (auto it = trade.localParts.begin(); it != trade.localParts.end();) {
    // Clear out old local parts
    if (now > it->first + LOCAL_PART_TIMEOUT_SECS) {
      it = trade.localParts.erase(it);
      ESP_LOGI(ENGINE_TAG, "Removed expired local part %s (user %d)", game::EnumNameShipPartType(it->second.type), it->second.creator);
    } else {
      const auto seq = getUserButtonSequence(it->second.creator);
      if (trade.codeBuffer.size() == seq.size() && std::equal(trade.codeBuffer.begin(), trade.codeBuffer.end(), seq.begin())) {
        ESP_LOGI(ENGINE_TAG, "Trade sequence matches part %s from user %d", game::EnumNameShipPartType(it->second.type), it->second.creator);
        auto newpart = new game::ShipPartT(it->second);
        bool alreadyhad = false;
        // If we get a part that we already have, ignore the new one.
        // this is a hack: std::remove and std::erase don't work for some
        // reason.
        for (int i = 0; i < state.parts.size(); i++) {
          if (state.parts[i]->type == newpart->type) {
            state.parts[i] = std::unique_ptr<game::ShipPartT>(new game::ShipPartT(it->second));
            alreadyhad = true;
          }
        }
        if (!alreadyhad) {
          state.parts.emplace_back(std::unique_ptr<game::ShipPartT>(newpart));
        }
        trade.codeBuffer.clear();
      }
      it++;
    }
  }
}

void Engine::tradeMakePart(const game::ShipPartT& part) {
  // A different user is broadcasting a part for offer.
  // Add it to the list of local parts, replacing any prior parts
  // offered by the user.
  for (int i = 0; i < trade.localParts.size(); i++) {
    if (trade.localParts[i].second.creator == part.creator) {
      trade.localParts[i] = std::make_pair(time(NULL),game::ShipPartT(part));
      ESP_LOGI(ENGINE_TAG, "Replaced existing part, seq %s", userButtonSequenceStr(getUserButtonSequence(part.creator)).c_str());
      return;
    }
  }
  trade.localParts.push_back(std::make_pair(time(NULL),game::ShipPartT(part)));
  ESP_LOGI(ENGINE_TAG, "Appended part, seq %s", userButtonSequenceStr(getUserButtonSequence(part.creator)).c_str());
}
