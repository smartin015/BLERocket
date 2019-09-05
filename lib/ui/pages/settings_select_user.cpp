#include "ui.h"
#include <iostream>

// Player wants to select a particular user to play as
void UI::drawSettingsSelectUser(const Engine* engine) {
  drawText("SettingsSelectUser", TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO selectable list of users (based on SPIFFS file)
}
