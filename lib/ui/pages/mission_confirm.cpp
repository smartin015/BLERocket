#include "ui.h"
#include <iostream>

// Player about to confirm mission
void UI::drawMissionConfirm(const Engine* engine) {
  drawText("Confirm Mission", TITLE_SZ, TITLE_X, TITLE_Y);
  // TODO Details
  drawText("Launch Y/N?", TITLE_SZ, BODY_X, BODY_Y);
}
