#include "ui.h"
#include <iostream>

void UI::drawTradeEntry(const Engine* engine) {
  drawText("Trade", TITLE_SZ, TITLE_X, TITLE_Y);

  // Draw our part
  game::ShipPartT userPart = engine->getUserPart();
  drawText(game::EnumNameShipPartType(userPart.type), SZ_S, BODY_X, BODY_Y);
  drawText(std::to_string(userPart.quality), SZ_S, BODY_X + SZ_M, BODY_Y);

  // Draw our ID sequence
  auto seq = getUserButtonSequence(engine->getState()->status->user);
  for (int i = 0; i < seq.size(); i++) {
    switch (seq[i]) {
      case nav::Command_down:
        drawText("v", SZ_S, BODY_X + (2*SZ_M) + (SZ_M * i), BODY_Y);
        break;
      case nav::Command_up:
        drawText("^", SZ_S, BODY_X + (2*SZ_M) + (SZ_M * i), BODY_Y);
        break;
      case nav::Command_right:
        drawText(">", SZ_S, BODY_X + (2*SZ_M) + (SZ_M * i), BODY_Y);
        break;
      case nav::Command_enter:
        drawText("X", SZ_S, BODY_X + (2*SZ_M) + (SZ_M * i), BODY_Y);
        break;
    }
  }

  // Draw parts collected from others
  const auto& parts = engine->getState()->parts;
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]->quality == 0) {
      continue;
    }
    std::string text = game::EnumNameShipPartType(parts[i]->type);
    // TODO show values
    drawText(text, SZ_S,  BODY_X, BODY_Y + SZ_M*((uint8_t)parts[i]->type+1));
    drawText(std::to_string(parts[i]->quality), SZ_S,  BODY_X + (2*SZ_M), BODY_Y + SZ_M*((uint8_t)parts[i]->type+1));
  }
}
