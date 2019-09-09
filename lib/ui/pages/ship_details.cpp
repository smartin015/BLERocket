#include "ui.h"
#include <iostream>

// Player wants to see more information about a ship (or start a mission)
void UI::drawShipDetails(const Engine* engine) {
  const game::StateT* state = engine->getState();
  const meta::DataT* data = engine->getData();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText("", true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< fleet",
      0, y_offset,
      NULL, &y_offset);
  y_offset = 0;
  x_offset += SIDEBAR_MARGIN;

  game::ShipPartT userPart = generatePart(state->status->user, state->status->score);

  setFont(&FONT_POPPINS_8);
  char buf[32];

  DrawStringAt(
      state->ships[state->selectedShip]->name.c_str(),
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  x_offset += 5;
  

  const auto& parts = state->ships[state->selectedShip]->parts;
  for (int i = 0; i < parts.size(); i++) {
    const auto& p = parts[i];

    setFont(&FONT_ROBOTO_6);

    switch (p->type) {
      case game::ShipPartType_thruster:
        DrawStringAt(
            "Thruster",
            x_offset, y_offset,
            NULL, &y_offset);
        break;

      case game::ShipPartType_cargo:
        DrawStringAt(
            "Cargo Bay",
            x_offset, y_offset,
            NULL, &y_offset);
        break;

      case game::ShipPartType_sensors:
        DrawStringAt(
            "Sensor Array",
            x_offset, y_offset,
            NULL, &y_offset);
        break;

      case game::ShipPartType_hull:
        DrawStringAt(
            "Hull",
            x_offset, y_offset,
            NULL, &y_offset);
        break;
      default:
        DrawStringAt(
            "Unknown part",
            x_offset, y_offset,
            NULL, &y_offset);
    }
    setFont(&FONT_TINY);
    snprintf(buf, sizeof(buf), "Made by %s", data->users[p->creator]->username.c_str());
    DrawStringAt(
        buf,
        x_offset + 5, y_offset,
        NULL, &y_offset);
    snprintf(buf, sizeof(buf), "Quality %d", p->quality);
    DrawStringAt(
        buf,
        x_offset + 5, y_offset,
        NULL, &y_offset);
  }

  setFont(&FONT_ROBOTO_6);

  y_offset = 20;
  x_offset = 150;
  DrawStringAt(
      "> Mission",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset += LINESPACING;
  DrawStringAt(
      "v Rename",
      x_offset, y_offset,
      NULL, &y_offset);
}
