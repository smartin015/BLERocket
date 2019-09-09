#include "ui.h"
#include <iostream>

#define NUM_MISSIONS 3
const message::Type MISSIONS[NUM_MISSIONS] = {
  message::Type_race,
  message::Type_trade,
  message::Type_explore,
};

// Player selecting a mission for a particular ship
void UI::drawMissionTypeSelect(const Engine* engine) {
  const game::StateT* state = engine->getState();

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText("", true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< destination",
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
  y_offset += LINESPACING;
  setFont(&FONT_TINY);
  DrawStringAt(
      "select a destination",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  3*LINESPACING;

  x_offset += 5;

  setFont(&FONT_ROBOTO_6);

  const auto* m = engine->getMission();
  std::vector<std::string> items;
  int idx = 0;
  for (int i = 0; i < NUM_MISSIONS; i++) {
    items.emplace_back(message::EnumNameType(MISSIONS[i]));
    if (m->type == MISSIONS[i]) {
      idx = i;
    }
  }
  drawSelector(items, idx, x_offset, y_offset);
}
