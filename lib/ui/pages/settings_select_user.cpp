#include "ui.h"
#include <iostream>

// Player wants to select a particular user to play as
void UI::drawSettingsSelectUser(const Engine* engine) {
  drawText("Select User", TITLE_SZ, TITLE_X, TITLE_Y);
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();
  const int top = std::max(0, id-2);
  std::vector<std::string> items;
  for (int i = top; i < SELECTOR_NUM_ITEMS && i < data->users.size(); i++) {
    items.emplace_back(data->users[i]->username);
  }
  drawSelector(items, id-top, BODY_X, BODY_Y);
}
