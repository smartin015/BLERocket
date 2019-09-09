#include "ui.h"
#include <iostream>

// Player wants to reset the device
void UI::drawSettingsReset(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  DrawStringAt(
      "Confirm Reset",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset += 3 * LINESPACING;
  x_offset += 5;

  setFont(&FONT_ROBOTO_6);

  char buf[32];
  DrawStringAt(
      "This will reset your device.",
      x_offset, y_offset,
      NULL, &y_offset);
  DrawStringAt(
      "All data will be lost.",
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
