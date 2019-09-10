#include "ui.h"
#include <iostream>

// User selecting action to perform on visiting ship
void UI::drawShipVisitDecision(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  const auto* data = engine->getData();
  char buf[48];

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
      "What will you do?",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  3*LINESPACING;
  x_offset += 5;

  std::vector<std::string> items;
  for (int i = 0; i < e->choices.size(); i++) {
    items.push_back(e->scenario->choices[e->choices[i]]->action);
  }
  drawSelector(items, e->selectedChoice, x_offset, y_offset);
}
