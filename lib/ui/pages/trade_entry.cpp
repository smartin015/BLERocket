#include "ui.h"
#include <iostream>
#include <string>


void UI::drawTradeEntry(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText("", true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< main",
      0, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  x_offset += SIDEBAR_MARGIN;


  setFont(&FONT_POPPINS_8);

  DrawStringAt(
      "Trade Parts",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  x_offset += 10;

  setFont(&FONT_ROBOTO_6);
  // Draw our part
  const game::StateT* state = engine->getState();
  game::ShipPartT userPart = generatePart(state->status->user, state->status->score);
  std::string produce = "Your factory produces ";
  switch(userPart.type) {
    case game::ShipPartType_hull:
      produce += "hulls";
      break;
    case game::ShipPartType_thruster:
      produce += "thrusters";
      break;
    case game::ShipPartType_cargo:
      produce += "cargo bays";
      break;
    case game::ShipPartType_sensors:
      produce += "sensor arrays";
      break;
  }
  DrawStringAt(
      produce,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  std::string qual = "Your workers have ";
  qual += userPart.quality;
  qual += " experience";
  DrawStringAt(
      qual,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;


  char buf[32];
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
