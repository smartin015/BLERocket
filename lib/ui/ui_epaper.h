#ifdef UI_EPAPER
#ifndef UI_EPAPER_H
#define UI_EPAPER_H

#include "nav_generated.h"
#include "ui.h"
#include "engine.h"
#include <memory>
#include "GxEPD2_BW.h"

#define UI_TAG "ui_epaper"
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
  void drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y);
  bool flush();
private:
  // TODO
  GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display;
  void DrawNametagScreen();
  void DrawSidebarText(std::string text, bool leftside);
};

#endif // UI_EPAPER_H
#endif // UI_EPAPER
