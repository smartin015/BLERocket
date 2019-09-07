#include "ui.h"
#include <iostream>
#include <string>


void UI::drawTradeEntry(const Engine* engine) {
  drawText("Trade", TITLE_SZ, TITLE_X, TITLE_Y);

  // Draw our part
  game::ShipPartT userPart = engine->getUserPart();
  drawText(game::EnumNameShipPartType(userPart.type), SZ_S, BODY_X, BODY_Y);
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", userPart.quality);
  drawText(buf, SZ_S, BODY_X + SZ_M, BODY_Y);

  // Draw our ID sequence
  auto seq = userButtonSequenceStr(getUserButtonSequence(engine->getState()->status->user));
  drawText(seq, SZ_S, BODY_X + (2*SZ_M), BODY_Y);

  // Draw parts collected from others
  const auto& parts = engine->getState()->parts;
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]->quality == 0) {
      continue;
    }
    int l = (parts[i]->type == game::ShipPartType_hull || parts[i]->type == game::ShipPartType_thruster);
    int t = (parts[i]->type == game::ShipPartType_hull || parts[i]->type == game::ShipPartType_cargo);
    drawText(game::EnumNameShipPartType(parts[i]->type), SZ_S,
      BODY_X + 3*SZ_M*l,
      BODY_Y + SZ_M + SZ_M*t);
    snprintf(buf, sizeof(buf), "%d", parts[i]->quality);
    drawText(buf, SZ_S,
      BODY_X + (2*SZ_M) + 3*SZ_M*l,
      BODY_Y + SZ_M + SZ_M*t);
  }
}
