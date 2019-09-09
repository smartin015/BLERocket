#include "ui.h"
#include <iostream>

// Main landing page (and badge display)
void UI::drawMain(const Engine* engine) {
  setRotation(ROTATION_GAME);
  DrawSidebarText("", true);
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();
  int score = engine->getState()->status->score;
  int rep = engine->getState()->status->reputation;

  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;;
  int y_offset = 0;

  setFont(&FONT_POPPINS_12);

  DrawStringAt(
      "Rockets n'at!",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  setFont(&FONT_TINY);
  DrawStringAt(
      "by semartin@ and jeffcooper@",
      x_offset, y_offset,
      NULL, &y_offset);
  DrawStringAt(
      "from Pittsburgh - go/rocketsnat",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  2 * LINESPACING;

  setFont(&FONT_ROBOTO_6);
  char buf[32];
  snprintf(buf, sizeof(buf), "score:      %d", score);
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  // TODO - gate showing rep on phase 2?
  snprintf(buf, sizeof(buf), "reputation: %d", rep);
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  y_offset +=  3 * LINESPACING;

  setFont(&FONT_ROBOTO_6);
  int controls_line_1 = y_offset;
  DrawStringAt(
      "^ Launch!",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  int controls_line_2 = y_offset;
  DrawStringAt(
      "v Fleet",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  x_offset += 120;
  y_offset = controls_line_1;
  DrawStringAt(
      "> Parts",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset = controls_line_2;
  DrawStringAt(
      "* Settings",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  // TODO active events
  // TODO visiting rockets
}
