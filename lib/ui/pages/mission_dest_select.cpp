#include "ui.h"
#include <iostream>

#define MAX_DESTINATIONS 4

// Player selecting a mission destination
void UI::drawMissionDestSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText("", true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< details",
      0, y_offset,
      NULL, &y_offset);
  x_offset += SIDEBAR_MARGIN;
  char buf[32];
  snprintf(buf, sizeof(buf), "%s's mission", state->ships[state->selectedShip]->name.c_str());
  setFont(&FONT_POPPINS_8);
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  setFont(&FONT_TINY);
  DrawStringAt(
      "select a mission type",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  3*LINESPACING;

  x_offset += 5;

  setFont(&FONT_ROBOTO_6);

  // TODO maybe order by RSSI?
  const mission_state_t* m = engine->getMission();
  if (m->localStatus.size() == 0) {
    setFont(&FONT_ROBOTO_6);
    DrawStringAt(
        "No nearby systems",
        x_offset, y_offset,
        NULL, &y_offset);
    DrawStringAt(
        "Find some friends!",
        x_offset, y_offset,
        NULL, &y_offset);
    return;
  }

  std::vector<std::string> items;
  const meta::DataT* data = engine->getData();
  for (int i = 0; i < m->localStatus.size() && i < MAX_DESTINATIONS; i++) {
    items.emplace_back(data->users[m->localStatus[i].second.user]->username);
  }

  drawSelector(items, state->selectedUser, x_offset, y_offset);
}
