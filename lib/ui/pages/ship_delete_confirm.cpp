#include "ui.h"
#include <iostream>

// Player about to confirm ship delete
void UI::drawShipDeleteConfirm(const Engine* engine) {
  const game::StateT* state = engine->getState();
  const auto* data = engine->getData();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< back",
      0, y_offset,
      NULL, &y_offset);
  x_offset += SIDEBAR_MARGIN;
  setFont(&FONT_POPPINS_8);
  DrawStringAt(
      "Confirm Deletion",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset += 3 * LINESPACING;
  x_offset += 5;

  setFont(&FONT_ROBOTO_6);

  char buf[32];
  snprintf(buf, sizeof(buf),
      "Delete %s?", 
      state->ships[state->selectedShip]->name.c_str());

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  DrawStringAt(
      "This cannot be undone!",
      x_offset, y_offset,
      NULL, &y_offset);


  y_offset +=  2*LINESPACING;
  x_offset += 30;

  setFont(&FONT_ROBOTO_8);
  DrawStringAt(
      "X  Confirm",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  DrawStringAt(
      "<  Go back",
      x_offset, y_offset,
      NULL, &y_offset);
}
