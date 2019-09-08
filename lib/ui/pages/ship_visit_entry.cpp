#include "ui.h"
#include <iostream>

// Another player's ship is visiting this device.
void UI::drawShipVisitEntry(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  char buf[32];
  snprintf(buf, sizeof(buf), "%s %s", ms->ship->name.c_str(), message::EnumNameType(ms->action));
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  const auto* data = engine->getData();
  drawText(data->users[e->message.source_user]->username, SZ_S, BODY_X, BODY_Y);

  // TODO: wrap flavortext
  drawText(e->scenario->desc, SZ_S, BODY_X, BODY_Y + SZ_S);
}
