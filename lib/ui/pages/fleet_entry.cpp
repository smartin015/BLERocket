#include "ui.h"
#include <iostream>

// Page for this player's fleet of ships
void UI::drawFleetEntry(const Engine* engine) {
  drawText("Fleet", TITLE_SZ, TITLE_X, TITLE_Y);

  const game::StateT* state = engine->getState();
  if (state->ships.size() == 0) {
    drawText("You have no ships.", SZ_M, BODY_X, BODY_Y);
    return;
  }

  const int top = std::max(0, state->selectedShip-2);
  std::vector<std::string> items;
  for (int i = top; i < SELECTOR_NUM_ITEMS && i < state->ships.size(); i++) {
    items.emplace_back(state->ships[i]->name);
  }
  drawSelector(items, state->selectedShip - top, BODY_X, BODY_Y);
}
