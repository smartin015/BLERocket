#ifdef UI_EPAPER

#include "ui_epaper.h"

UIEPaper::UIEPaper() {
  // TODO
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
