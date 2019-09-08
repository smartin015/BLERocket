#include "engine.h"

const event_state_t* Engine::getEvent() const {
  return &event;
}

void Engine::ackEvent() {
  ESP_LOGI(ENGINE_TAG, "Event acked");
  event.acked = true;
}
