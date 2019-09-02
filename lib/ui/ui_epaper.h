#ifdef UI_EPAPER
#ifndef UI_EPAPER_H
#define UI_EPAPER_H

#include "nav_generated.h"
#include "ui.h"
#include "engine.h"
#include <memory>
#include "GxEPD2_BW.h"

#define WINDOW_SCALE 2
#define EPAPER_W_PX  250
#define EPAPER_H_PX  122

class UIEPaper : public UI {
public:
  UIEPaper();
  Command nextCommand();
  void clear();
  void drawText(const std::string& text, const int& size, const int& x, const int& y);
  void drawShape(const std::vector<std::pair<int, int>>& points);
  bool flush();
private:
  // TODO
  GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display;
};

#endif // UI_EPAPER_H
#endif // UI_EPAPER
