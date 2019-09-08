#include "ui.h"
#include <iostream>

// Player wants to see more information about a ship (or start a mission)
void UI::drawShipDetails(const Engine* engine) {
  const game::StateT* state = engine->getState();
  const meta::DataT* data = engine->getData();

  drawText(state->ships[state->selectedShip]->name, TITLE_SZ, TITLE_X, TITLE_Y);
  for (int i = 0; i < state->ships[state->selectedShip]->parts.size(); i++) {
    const auto& p = state->ships[state->selectedShip]->parts[i];
    char buf[24];
    snprintf(buf, sizeof(buf), "%s %d (%s)", game::EnumNameShipPartType(p->type), p->quality, data->users[p->creator]->username.c_str());
    drawText(buf, SZ_S, BODY_X, BODY_Y + SZ_S + (i*SZ_S));
  }
}
