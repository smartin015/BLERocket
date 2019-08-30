#include "ui.h"
#include <iostream>

// Player is preparing to launch a rocket
void UI::drawLaunchEntry(const Engine& engine) {
  drawText("Launch", TITLE_SZ, TITLE_X, TITLE_Y);
  const auto& parts = engine.getParts();
  for (const auto& kv : parts) {
    if (kv.second == 0) {
      drawText("Missing part " + std::string(game::EnumNameShipPartType(kv.first)), SZ_S, BODY_X, BODY_Y);
      return;
    }
  }
  drawText("3...2...1...", SZ_S, BODY_X, BODY_Y);
}
