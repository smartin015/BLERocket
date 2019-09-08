#include "ui.h"
#include <iostream>

#define MAX_DESTINATIONS 4

// Player selecting a mission destination
void UI::drawMissionDestSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();
  char buf[32];
  snprintf(buf, sizeof(buf), "%s mission", state->ships[state->selectedShip]->name.c_str());
  drawText(buf, TITLE_SZ, TITLE_X, TITLE_Y);

  // TODO maybe order by RSSI?
  const mission_state_t* m = engine->getMission();
  if (m->localStatus.size() == 0) {
    drawText("No targets nearby.\nFind some friends!", SZ_S, BODY_X, BODY_Y);
    return;
  }

  std::vector<std::string> items;
  const meta::DataT* data = engine->getData();
  for (int i = 0; i < m->localStatus.size() && i < MAX_DESTINATIONS; i++) {
    items.emplace_back(data->users[m->localStatus[i].second.user]->username);
  }

  drawSelector(items, state->selectedUser, BODY_X, BODY_Y);
}
