#include "ui.h"
#include <iostream>

void UI::drawFleetEntry(const Engine& engine) {
  drawText("Fleet", TITLE_SZ, TITLE_X, TITLE_Y);
  const auto& parts = engine.getParts();
  for (const auto& kv : parts) {
    if (kv.second == 0) {
      drawText("Missing part " + enumStr(kv.first), SZ_S, BODY_X, BODY_Y);
      return;
    }
  }
  drawText("3...2...1...", SZ_S, BODY_X, BODY_Y);
}
