#include "ui.h"
#include <iostream>

// Player wishes to change some settings
void UI::drawSettingsEntry(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_POPPINS_8);

  y_offset = 0;
  DrawStringAt(
      "Settings",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  5*LINESPACING;
  x_offset += 10;

  setFont(&FONT_ROBOTO_8);
  DrawStringAt(
      "< Back",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  DrawStringAt(
      "v Select User",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  DrawStringAt(
      "^ Reset device",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  DrawStringAt(
      "X Display Nametag",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
}
