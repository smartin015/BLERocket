#include "ui.h"
#include <iostream>

#define NUM_MISSIONS 3
const message::Type MISSIONS[NUM_MISSIONS] = {
  message::Type_race,
  message::Type_trade,
  message::Type_explore,
};

// Player selecting a mission for a particular ship
void UI::drawShipMissionSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();
  char buf[32];
  snprintf(buf, sizeof(buf), "%s mission", state->ships[state->selectedShip]->name.c_str());
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  const auto* m = engine->getMission();
  std::vector<std::string> items;
  int idx = 0;
  for (int i = 0; i < NUM_MISSIONS; i++) {
    items.emplace_back(message::EnumNameType(MISSIONS[i]));
    if (m->type == MISSIONS[i]) {
      idx = i;
    }
  }
  drawSelector(items, idx, BODY_X, BODY_Y);
}
