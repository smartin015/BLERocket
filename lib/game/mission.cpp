#include "engine.h"

const mission_state_t* Engine::getMission() const {
  return &mission;
}

void Engine::missionLoop(CommsBase* comms) {
  // timer-based periodic broadcast of status
  time_t now = time(NULL);
  if (mission.lastStatus + STATUS_ANNOUNCE_SECS < now) {
    ESP_LOGI(ENGINE_TAG, "Broadcasting status");
    message::MessageT msg;
    msg.source_user = state.status->user;
    msg.oneof.Set<game::StatusT>(game::StatusT());
    auto* s = msg.oneof.Asstatus();
    *s = *(state.status);
    comms->sendMessage(msg, false);
    mission.lastStatus = now;
  } else {
    time_t now = time(NULL);
    for (auto it = mission.localStatus.begin(); it != mission.localStatus.end();) {
      // Clear out old local statuses
      if (now > it->first + LOCAL_STATUS_TIMEOUT_SECS) {
        it = mission.localStatus.erase(it);
        ESP_LOGI(ENGINE_TAG, "Removed expired local status");
      } else {
        it++;
      }
    }
  }
}

void Engine::missionHandleStatus(const game::StatusT& status) {
  ESP_LOGI(STATUS_TAG, "Status: FirmwareVersion %d Score %d User %d Phase %d (tx %d)",
     uint16_t(status.firmwareVersion),
     status.score,
     uint16_t(status.user),
     uint16_t(status.phase_id),
     uint16_t(status.phase_txn));

  // Cheat by allowing self-status
  // if (status.user == state.status->user) {
  //   return;
  // }

  // Add to the list of statuses, replacing any prior statuses
  // from the same user.
  for (int i = 0; i < mission.localStatus.size(); i++) {
    if (mission.localStatus[i].second.user == status.user) {
      mission.localStatus[i] = std::make_pair(time(NULL),game::StatusT(status));
      ESP_LOGI(ENGINE_TAG, "Replaced existing status");
      return;
    }
  }
  mission.localStatus.push_back(std::make_pair(time(NULL),game::StatusT(status)));
  ESP_LOGI(ENGINE_TAG, "Appended status");
}

void Engine::missionUpdateScore() {
  const auto* choice = event.scenario->choices[event.selectedChoice].get();
  if (event.d20 >= choice->risk) {
    // Riskier choices have bigger rewards.
    // Higher reputation gives greater payout.
    event.scoreDelta = choice->risk * 10;
  } else {
    // Higher reputation means more penalty for failure
    event.scoreDelta = - choice->risk * 10;
  }
  
  state.status->score += event.scoreDelta;
}
