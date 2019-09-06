#include "engine.h"

void Engine::tradeLoop(CommsBase* comms) {
  // Periodically announce trades
  time_t now = time(NULL);
  if (state.page == nav::Page_tradeEntry) {
    if (lastTradeAnnounce + TRADE_ANNOUNCE_SECS < now) {
      ESP_LOGI(ENGINE_TAG, "Announcing trade");
      message::MessageT msg;
      msg.oneof.Set<message::PartT>(message::PartT());
      auto* s = msg.oneof.Aspart();
      s->action = message::Type_make;
      s->dest_user = 0; // 0 reaches all users
      s->part.reset(new game::ShipPartT());

      // TODO calculate part type and quality
      s->part->type = game::ShipPartType_hull;
      s->part->quality = 5;

      comms->sendMessage(msg, false);
      lastTradeAnnounce = now;
    }
  } else if (lastTradeAnnounce != 0) {
    lastTradeAnnounce = 0;
  }
}
void Engine::tradeInput(const nav::Command& cmd, CommsBase* comms) {
  if (cmd == nav::Command_up) {
    // Test user action to "receive" a part (really just increment)
    // TODO: based on a button code, receive a part listed in .
    ESP_LOGI(ENGINE_TAG, "Receiving all parts (testing)");
    if (state.parts.size() == 0) {
      for (int i = game::ShipPartType_MIN; i <= game::ShipPartType_MAX; i++) {
        auto part = std::unique_ptr<game::ShipPartT>(new game::ShipPartT());
        part->type = (game::ShipPartType) i;
        part->quality = 1;
        part->creator = 2; // TODO
        state.parts.emplace_back(std::move(part));
      }
    }
  }
}

void Engine::tradeMakePart(const game::ShipPartT& part) {
  // A different user is broadcasting a part for offer.
  // Add it to the list of local parts, replacing any prior parts
  // offered by the user.
  for (int i = 0; i < localParts.size(); i++) {
    if (localParts[i].second.creator == part.creator) {
      localParts[i] = std::make_pair(time(NULL),game::ShipPartT(part));
      ESP_LOGI(ENGINE_TAG, "Replaced existing part");
    }
    return;
  }
  localParts.push_back(std::make_pair(time(NULL),game::ShipPartT(part)));
  ESP_LOGI(ENGINE_TAG, "Appended part");
}
