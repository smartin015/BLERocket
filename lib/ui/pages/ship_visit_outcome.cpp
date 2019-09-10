#include "ui.h"
#include <iostream>

// User acted on ship; sees outcome of action
void UI::drawShipVisitOutcome(const Engine* engine) {
  const auto* e = engine->getEvent();
  const auto* ms = e->message.oneof.Asship();
  const auto* data = engine->getData();
  const auto* choice = e->scenario->choices[e->selectedChoice].get();
  char buf[48];

  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  x_offset += SIDEBAR_MARGIN;

  setFont(&FONT_POPPINS_8);

  DrawStringAt(
      "Captain's Log",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  3*LINESPACING;
  x_offset += 5;

  std::string narrative;
  // TODO show points earned
  if (e->d20 >= choice->risk) {
    narrative = choice->success;
  } else {
    narrative = choice->failure;
  }
  int i = 0;
  int j = 0;
  setFont(&FONT_TINY);
  while (i < narrative.size()) {
    char c = narrative[i];
    if (c == '\n' || j >= sizeof(buf)) {
      buf[j] = '\0';
      drawText(buf, 0, x_offset, y_offset);
      y_offset += 8;
      j = 0;
      i++;
      continue;
    }
    buf[j++] = narrative[i++];
  }
  buf[j] = '\0';
  drawText(buf, 0, x_offset, y_offset);

  y_offset += 3*LINESPACING;

  setFont(&FONT_ROBOTO_6);
  snprintf(buf, sizeof(buf), "Score:      %+d", e->scoreDelta);
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  drawText("Press any key to continue", 0, 50, EPAPER_SHORT_DIMENSION - 11);
}
