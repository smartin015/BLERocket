#include "ui.h"
#include <iostream>

void UI::drawTradeEntry(const Engine& engine) {
  drawText("Trade", TITLE_SZ, TITLE_X, TITLE_Y);

  const auto& parts = engine.getParts();
  for (const auto& kv : parts) {
    if (kv.second == 0) {
      continue;
    }
    std::string text = game::EnumNameShipPartType(kv.first);
    drawText(text + " " + std::to_string(kv.second), SZ_S,  BODY_X, BODY_Y + SZ_M*((uint8_t)kv.first));
  }
}
