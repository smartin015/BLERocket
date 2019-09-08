#include "engine.h"

message::Type Engine::getMission() const {
  return mission.type;
}

void Engine::missionLoop(CommsBase* comms) {
  // timer-based periodic broadcast of status
  time_t now = time(NULL);
  if (mission.lastStatus + STATUS_ANNOUNCE_SECS < now) {
    ESP_LOGI(ENGINE_TAG, "Broadcasting status");
    message::MessageT msg;
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
  ESP_LOGI(ENGINE_TAG, "Status: FirmwareVersion %d Site %d Score %d Rep %d User %d Phase %d (tx %d)",
     uint16_t(status.firmwareVersion),
     uint16_t(status.site),
     status.score,
     status.reputation,
     uint16_t(status.user),
     uint16_t(status.phase_id),
     uint16_t(status.phase_txn));

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
