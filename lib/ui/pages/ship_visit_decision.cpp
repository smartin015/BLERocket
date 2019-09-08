#include "ui.h"
#include <iostream>

// User selecting action to perform on visiting ship
void UI::drawShipVisitDecision(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  char buf[32];
  snprintf(buf, strlen(buf), "%s Decision", message::EnumNameType(ms->action));
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO list possible actions
  const auto* data = engine->getData();
  std::vector<std::string> items;
  for (int i = 0; i < SELECTOR_NUM_ITEMS && i < e->scenario->choices.size(); i++) {
    items.push_back(e->scenario->choices[i]->action);
  }
  drawSelector(items, e->selectedChoice, BODY_X, BODY_Y);
}
