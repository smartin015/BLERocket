#include "ui.h"
#include <iostream>

#define MAX_DESTINATIONS 4

// Player selecting a mission destination
void UI::drawShipDestSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();
  char buf[32];
  const int shipIdx = engine->getSelectedShipIdx();
  snprintf(buf, sizeof(buf), "%s target", state->ships[shipIdx]->name.c_str());
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO maybe order by RSSI?
  const std::vector<std::pair<time_t, game::StatusT>>* ss = engine->getNearbyClientStatuses();
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
