#include "ui.h"
#include <iostream>

// Player wants to reset the device
void UI::drawSettingsReset(const Engine* engine) {
  drawText("SettingsReset", TITLE_SZ, TITLE_X, TITLE_Y);
  drawText("Reset Y/N?", TITLE_SZ, BODY_X, BODY_Y);
}
