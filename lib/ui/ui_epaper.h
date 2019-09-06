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

#define ROTATION_GAME 3
#define ROTATION_NAMETAG 1
#define ROTATION_GAME_LEFTSIDE 0
#define ROTATION_GAME_RIGHTSIDE 2
#define ROTATION_NAMETAG_RIGHTSIDE 0
#define ROTATION_NAMETAG_LEFTSIDE 2

#define SIDEBAR_WIDTH 15
#define SIDEBAR_MARGIN 15

#define NAMETAG_TOP_MARGIN 0
#define LINESPACING 0

#define EPAPER_LONG_DIMENSION 250
#define EPAPER_SHORT_DIMENSION 122

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
  void DrawNametagScreen(
      std::string firstname,
      std::string lastname,
      std::string username,
      std::string site);
  void DrawSidebarText(std::string text, bool leftside);
  const GFXfont* PickBestFontForString(std::string s, int maxwidth, const GFXfont* const fonts[]);
  void DrawStringWithin(
      std::string s,           // string to draw
      int x, int y,            // where to draw.
      int* xmax, int* ymax,    // where to store bottom right coords of bounds
      int maxw,                // maximum width for drawing
      const GFXfont* const fonts[] // fonts to pick from
      );
};

#endif // UI_EPAPER_H
#endif // UI_EPAPER
