#include "ui.h"
#include <iostream>

// Player wants to see more information about a ship (or start a mission)
void UI::drawShipDetails(const Engine* engine) {
  drawText("ShipDetails", TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO:
  // - ship name
  // - parts, manufacturers, other details
}
