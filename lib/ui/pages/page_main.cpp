#include "ui.h"
#include <iostream>

// Main landing page (and badge display)
void UI::drawMain(const Engine* engine) {
  // TODO user name, location, username
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();

  char buf[16];
  snprintf(buf, sizeof(buf), "%d", engine->getState()->status->score);
  drawText(buf, SZ_S, BODY_X, BODY_Y + SZ_L);

  snprintf(buf, sizeof(buf), "%d", engine->getState()->status->reputation);
  drawText(buf, SZ_S, BODY_X, BODY_Y + SZ_L + SZ_S);
  // TODO active events
  // TODO visiting rockets
}
