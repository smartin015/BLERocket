#include "ui.h"
#include <iostream>

void UI::drawTradeEntry(const Engine* engine) {
  drawText("Trade", TITLE_SZ, TITLE_X, TITLE_Y);

  const auto& parts = engine->getState()->parts;
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]->quality == 0) {
      continue;
    }
    std::string text = game::EnumNameShipPartType(parts[i]->type);
    // TODO show values
    drawText(text, SZ_S,  BODY_X, BODY_Y + SZ_M*((uint8_t)parts[i]->type));
  }
}
