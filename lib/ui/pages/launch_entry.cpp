#include "ui.h"
#include <iostream>

// Player is preparing to launch a rocket
void UI::drawLaunchEntry(const Engine* engine) {
  drawText("Launch", TITLE_SZ, TITLE_X, TITLE_Y);
  const auto& parts = engine->getState()->parts;
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]->quality == 0) {
      drawText("Missing part " + std::string(game::EnumNameShipPartType(parts[i]->type)), SZ_S, BODY_X, BODY_Y);
      return;
    }
  }
  drawText("3...2...1...", SZ_S, BODY_X, BODY_Y);
}
