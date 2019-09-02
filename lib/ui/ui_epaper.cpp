#ifdef UI_EPAPER

#include "ui_epaper.h"
#include "GxEPD2_BW.h"
#include <Fonts/FreeMonoBold9pt7b.h>


UIEPaper::UIEPaper() {
  // TODO
  GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(GxEPD2_213_B72(14, 27, 33, -1)); // GDEH0213B72
  display.init(115200);

  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds("Hello PIO", 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print("Hello PIO");
  }
  while (display.nextPage());

}

Command UIEPaper::nextCommand() {
  // TODO
  return nav::Command_unknown;
}

void UIEPaper::clear() {
  // TODO
}

bool UIEPaper::flush() {
  // TODO
  return false;
}

void UIEPaper::drawText(const std::string& text, const int& size, const int& x, const int& y) {
  // TODO
}

void UIEPaper::drawShape(const std::vector<std::pair<int, int>>& points) {
  // TODO
}

#endif // UI_EPAPER
