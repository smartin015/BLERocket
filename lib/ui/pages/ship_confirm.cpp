#include "ui.h"
#include <iostream>

// Player about to confirm mission
void UI::drawShipConfirm(const Engine* engine) {
  drawText("ShipConfirm", TITLE_SZ, TITLE_X, TITLE_Y);
  drawText("Launch Y/N?", TITLE_SZ, BODY_X, BODY_Y);
}
