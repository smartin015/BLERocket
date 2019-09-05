#include "ui.h"
#include <iostream>

// Player wants to reset the device
void UI::drawSettingsReset(const Engine* engine) {
  drawText("SettingsReset", TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO Display Y/N? confirm prompt
}
