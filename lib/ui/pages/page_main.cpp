#include "ui.h"
#include <iostream>

// Main landing page (and badge display)
void UI::drawMain(const Engine* engine) {
  // TODO user name, location, username
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();
  drawText(data->users[id]->name, SZ_M, TITLE_X, TITLE_Y);
  drawText(data->users[id]->username, SZ_S, BODY_X + SZ_L, BODY_Y);
  drawText(data->sites[data->users[id]->site]->shortname, SZ_S, BODY_X, BODY_Y);

  char buf[16];
  snprintf(buf, sizeof(buf), "%d", engine->getState()->status->score);
  drawText(buf, SZ_S, BODY_X, BODY_Y + SZ_L);
  // TODO active events
  // TODO visiting rockets
}
