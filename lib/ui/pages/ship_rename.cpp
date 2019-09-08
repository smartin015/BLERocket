#include "ui.h"
#include <iostream>

// Player wants to rename ship
void UI::drawShipRename(const Engine* engine) {
  drawText("Rename", TITLE_SZ, TITLE_X, TITLE_Y);
  const game::StateT* state = engine->getState();
  const auto& ship = state->ships[state->selectedShip];
  drawText("_", SZ_S, BODY_X + (state->charIdx * SZ_S), BODY_Y);

  for (int i = 0; i < MAX_SHIP_NAME_LEN; i++) {
    char buf[2] = {ship->name[i], 0};
    drawText(buf, SZ_S, BODY_X + (i*SZ_S), BODY_Y);
  }
  // TODO text input with "Name:"
}
