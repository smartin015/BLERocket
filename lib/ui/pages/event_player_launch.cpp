#include "ui.h"
#include <iostream>

// Player has launched a rocket; this is a brag message for
// all other devices in range.
void UI::drawEventPlayerLaunch(const Engine& engine) {
  drawText("EventPlayerLaunch", TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO: Include:
  // - the player that launched it (and their score)
  // - contributors for each part
  // - neato animation
}
