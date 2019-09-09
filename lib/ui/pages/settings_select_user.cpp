#include "ui.h"
#include <iostream>

// Player wants to select a particular user to play as
void UI::drawSettingsSelectUser(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< settings",
      0, y_offset,
      NULL, &y_offset);

  setFont(&FONT_POPPINS_8);
  char buf[64];
  DrawStringAt(
      "Select User",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  6*LINESPACING;

  x_offset += 5;

  setFont(&FONT_ROBOTO_6);
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();
  const int top = std::max(1, id-2); // Skip 0 which is "null" user
  std::vector<std::string> items;
  for (int i = 0; i < SELECTOR_NUM_ITEMS && top+i < data->users.size(); i++) {
    items.emplace_back(data->users[top+i]->username);
  }
  drawSelector(items, id-top, x_offset, y_offset);
}
