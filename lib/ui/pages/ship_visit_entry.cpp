#include "ui.h"
#include <iostream>

// Another player's ship is visiting this device.
void UI::drawShipVisitEntry(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  const auto* data = engine->getData();
  char buf[48];

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< ignore",
      0, y_offset,
      NULL, &y_offset);
  x_offset += SIDEBAR_MARGIN;

  setFont(&FONT_POPPINS_8);

  DrawStringAt(
      "Ship detected!",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  x_offset += 5;

  snprintf(buf, sizeof(buf), 
      "%s hailing from %s@", 
      ms->ship->name.c_str(),
      data->users[ms->ship->owner]->username.c_str());
  setFont(&FONT_ROBOTO_6);

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  DrawStringAt(
      "has entered your sector!",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset += 3*LINESPACING;

  setFont(&FONT_TINY);
  // TODO - not this
  int i = 0;
  int j = 0;
  while (i < e->scenario->desc.size()) {
    char c = e->scenario->desc[i];
    if (c == '\n' || j >= sizeof(buf)) {
      buf[j] = '\0';
      drawText(buf, 0, x_offset, y_offset);
      y_offset += 8;
      j = 0;
      i++;
      continue;
    }
    buf[j++] = e->scenario->desc[i++];
  }
  buf[j] = '\0';
  drawText(buf, 0, x_offset, y_offset);

  setFont(&FONT_ROBOTO_6);

  DrawStringAt(
      "Next >",
      200, 100,
      NULL, NULL);
}
