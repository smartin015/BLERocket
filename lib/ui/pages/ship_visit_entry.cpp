#include "ui.h"
#include <iostream>

// Another player's ship is visiting this device.
void UI::drawShipVisitEntry(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  const auto* data = engine->getData();
  char buf[32];
  /*
  snprintf(buf, sizeof(buf), "%s %s", ms->ship->name.c_str(), message::EnumNameType(ms->action));
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  drawText(data->users[e->message.source_user]->username, SZ_S, BODY_X, BODY_Y);

  // TODO: wrap flavortext
  drawText(e->scenario->desc, SZ_S, BODY_X, BODY_Y + SZ_S);
*/
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

  setFont(&FONT_POPPINS_8);

  DrawStringAt(
      "Ship detected!",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  x_offset += 5;

  snprintf(buf, sizeof(buf), "A ship hailing from %s@", data->users[ms->ship->owner]->username.c_str());
  setFont(&FONT_ROBOTO_6);

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  DrawStringAt(
      "has entered your sector!",
      x_offset, y_offset,
      NULL, &y_offset);

}
