#include "engine.h"

const message::MessageT* Engine::getNotification() const {
  if (event.notifyAcked) {
    return NULL;
  }
  return &(event.notification);
}

void Engine::ackNotification() {
  event.notifyAcked = true;
}

const message::MessageT* Engine::peekMessage() const {
  if (event.messages.size() == 0) {
    return NULL;
  }
  return &(event.messages[0]);
}

void Engine::ackMessage() {
  if (event.messages.size() == 0) {
    return;
  }
  event.messages.erase(event.messages.begin());
}
