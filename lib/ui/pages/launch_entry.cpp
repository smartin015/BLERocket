#include "ui.h"
#include <iostream>

// Player is preparing to launch a rocket
void UI::drawLaunchEntry(const Engine* engine) {
  drawText("Launch", TITLE_SZ, TITLE_X, TITLE_Y);
  const auto& parts = engine->getState()->parts;
  if (!engine->readyToLaunch()) {
    drawText("Missing parts", SZ_S, BODY_X, BODY_Y);
    return;
  }
  drawText("3...2...1...", SZ_S, BODY_X, BODY_Y);
}
