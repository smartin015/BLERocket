#include "ui.h"
#include <iostream>

// Page for this player's fleet of ship's
void UI::drawFleetEntry(const Engine* engine) {
  drawText("Fleet", TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO: Include a selectable list of ship names
  // const auto* ships = engine->getState()->ships;

  // if (ships.size() == 0) {
  //   drawText("You have no ships.", SZ_M, BODY_X, BODY_Y);
  // } else {
  //   const int top = std::max(0, std::min(fleetTop, ships.size()));
  //   std::vector<std::string> items;
  //   for (int i = 0; i < SELECTOR_NUM_ITEMS && top+i < ships.size(); i++) {
  //     items.emplace_back(ships[i]->name);
  //   }
  //   drawSelector(items, fleetSelect, BODY_X, BODY_Y);
  // }
}
