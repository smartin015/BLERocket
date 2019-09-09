#include "ui.h"
#include <iostream>

// Player wants to rename ship
void UI::drawShipRename(const Engine* engine) {
  const game::StateT* state = engine->getState();
  const auto& ship = state->ships[state->selectedShip];
  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  setFont(&FONT_POPPINS_8);
  char buf[64];
  DrawStringAt(
      "Rename Ship",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  6*LINESPACING;

  x_offset += 40;

  setFont(&FONT_ROBOTO_8);
  char underline[MAX_SHIP_NAME_LEN];
  for (int i = 0; i < sizeof(underline); i++) {
    underline[i] = ' ';
  }
  underline[sizeof(underline) - 1] = '\0';

  underline[state->charIdx] = '^';
  drawText(underline, 0, x_offset, y_offset);
  y_offset += 25;
  underline[state->charIdx] = 'v';
  drawText(underline, 0, x_offset, y_offset);
  y_offset -= 16;

  std::cout << "\t\t" << state->charIdx << "\t'" << underline << "'\n";

  drawText(ship->name.c_str(), 0, x_offset, y_offset);
  
  setFont(&FONT_TINY);
  drawText("< > choose position", 0, SIDEBAR_WIDTH + SIDEBAR_MARGIN, EPAPER_SHORT_DIMENSION - 33);
  drawText("^ v change letter", 0, SIDEBAR_WIDTH + SIDEBAR_MARGIN, EPAPER_SHORT_DIMENSION - 22);
  drawText(" X  confirm", 0, SIDEBAR_WIDTH + SIDEBAR_MARGIN, EPAPER_SHORT_DIMENSION - 11);
}
