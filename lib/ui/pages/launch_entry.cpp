#include "ui.h"
#include <iostream>

// Player is preparing to launch a rocket
void UI::drawLaunchEntry(const Engine* engine) {
  const game::StateT* state = engine->getState();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< home",
      0, y_offset,
      NULL, &y_offset);
  x_offset += SIDEBAR_MARGIN;
  setFont(&FONT_POPPINS_8);
  DrawStringAt(
      "Launch",
      x_offset, y_offset,
      NULL, &y_offset);

  y_offset += 3 * LINESPACING;

  const auto& parts = engine->getState()->parts;
  if (!engine->readyToLaunch()) {
    setFont(&FONT_ROBOTO_6);
    DrawStringAt(
        "You're missing some parts!",
        x_offset, y_offset,
        NULL, &y_offset);
  setFont(&FONT_TINY);
    DrawStringAt(
        "come back when you have them all",
        x_offset, y_offset,
        NULL, &y_offset);
    return;
  }

  // TODO - it would be cool to animate this
  setFont(&FONT_POPPINS_18);
  DrawStringAt("3...2...1...", x_offset, y_offset, NULL, &y_offset);
  y_offset += 4*LINESPACING;
  setFont(&FONT_TINY);
  DrawStringAt("press X...", x_offset, y_offset, NULL, &y_offset);
}
