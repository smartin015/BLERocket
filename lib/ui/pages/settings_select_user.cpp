#include "ui.h"
#include <iostream>

// Player wants to select a particular user to play as
void UI::drawSettingsSelectUser(const Engine* engine) {
  drawText("Select User", TITLE_SZ, TITLE_X, TITLE_Y);
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();
  const int top = std::max(1, id-2); // Skip 0 which is "null" user
  std::vector<std::string> items;
  for (int i = 0; i < SELECTOR_NUM_ITEMS && top+i < data->users.size(); i++) {
    items.emplace_back(data->users[top+i]->username);
  }
  drawSelector(items, id-top, BODY_X, BODY_Y);
}
