#include "ui.h"
#include <iostream>

// Player about to confirm mission
void UI::drawMissionConfirm(const Engine* engine) {
  const game::StateT* state = engine->getState();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< type",
      0, y_offset,
      NULL, &y_offset);
  x_offset += SIDEBAR_MARGIN;
  setFont(&FONT_POPPINS_8);
  DrawStringAt(
      "Confirm Mission",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset += 3 * LINESPACING;
  x_offset += 5;

  setFont(&FONT_ROBOTO_6);

  char buf[32];
  snprintf(buf, sizeof(buf),
      "Send %s on a mission", 
      state->ships[state->selectedShip]->name.c_str());

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  snprintf(buf, sizeof(buf),
      "to %s", 
      message::EnumNameType(engine->getMission()->type));

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  snprintf(buf, sizeof(buf),
      "in %s@'s system?", 
      engine->getData()->users[state->selectedUser]->username.c_str());
  DrawStringAt(
      buf,
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
