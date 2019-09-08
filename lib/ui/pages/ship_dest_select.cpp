#include "ui.h"
#include <iostream>

#define MAX_DESTINATIONS 4

// Player selecting a mission destination
void UI::drawShipDestSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();
  char buf[32];
  snprintf(buf, sizeof(buf), "%s mission", state->ships[state->selectedShip]->name.c_str());
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO maybe order by RSSI?
  const std::vector<std::pair<time_t, game::StatusT>>* ss = engine->getNearbyClientStatuses();
  if (ss->size() == 0) {
    drawText("No targets nearby.\nFind some friends!", SZ_S, BODY_X, BODY_Y);
    return;
  }

  std::vector<std::string> items;
  int idx = 0;
  for (int i = 0; i < ss->size() && i < MAX_DESTINATIONS; i++) {
    // items.emplace_back(message::EnumNameType(MISSIONS[i]));
    // if (m == MISSIONS[i]) {
    //   idx = i;
    // }
  }


  drawSelector(items, idx, BODY_X, BODY_Y);
}
