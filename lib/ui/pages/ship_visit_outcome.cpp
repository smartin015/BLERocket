#include "ui.h"
#include <iostream>

// User acted on ship; sees outcome of action
void UI::drawShipVisitOutcome(const Engine* engine) {
  // TODO show points earned
  const auto* e = engine->getEvent();
  const auto* choice = e->scenario->choices[e->selectedChoice].get();
  if (e->d20 >= choice->risk) {
    drawText("Success!", TITLE_SZ, TITLE_X, TITLE_Y);
    drawText(choice->success, SZ_S, BODY_X, BODY_Y);
  } else {
    drawText("Failed!", TITLE_SZ, TITLE_X, TITLE_Y);
    drawText(choice->failure, SZ_S, BODY_X, BODY_Y);
  }
}
