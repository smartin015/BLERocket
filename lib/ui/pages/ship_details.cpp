#include "ui.h"
#include <iostream>

// Player wants to see more information about a ship (or start a mission)
void UI::drawShipDetails(const Engine* engine) {
  drawText("ShipDetails", TITLE_SZ, TITLE_X, TITLE_Y);

  const game::StateT* state = engine->getState();
  const int idx = engine->getSelectedShipIdx();

  drawText(state->ships[idx]->name, SZ_S, BODY_X, BODY_Y);
  // TODO
  // - parts, manufacturers, other details
}
