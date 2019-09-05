#include "ui.h"
#include <iostream>

// Player wishes to change some settings
void UI::drawSettingsEntry(const Engine* engine) {
  drawText("SettingsEntry", TITLE_SZ, TITLE_X, TITLE_Y);
}
