#include "ui.h"
#include <iostream>

// Page for this player's fleet of ships
void UI::drawFleetEntry(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< home",
      0, y_offset,
      NULL, &y_offset);
  y_offset = 0;
  x_offset += SIDEBAR_MARGIN;
  const game::StateT* state = engine->getState();

  setFont(&FONT_POPPINS_8);
  char buf[64];
  DrawStringAt(
      "Fleet Management",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  3*LINESPACING;


  setFont(&FONT_ROBOTO_6);
  if (state->ships.size() == 0) {
    DrawStringAt(
        "You have no ships!",
        x_offset, y_offset,
        NULL, &y_offset);
    y_offset +=  LINESPACING;
    DrawStringAt(
        "Come back after you launch some",
        x_offset, y_offset,
        NULL, &y_offset);
    return;
  }

  auto* m = engine->getMission();

  const int top = std::max(0, state->selectedShip-2);
  std::vector<std::string> items;
  for (int i = top; i < SELECTOR_NUM_ITEMS + top && i < state->ships.size(); i++) {
    items.emplace_back(state->ships[i]->name);
  }
  drawSelector(items, state->selectedShip - top, x_offset, y_offset);
}
