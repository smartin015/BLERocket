#ifdef UI_EPAPER
#ifndef UI_EPAPER_H
#define UI_EPAPER_H

#include "nav_generated.h"
#include "ui.h"
#include "engine.h"
#include <memory>
#include "GxEPD2_BW.h"

#include "fonts.h"

#define UI_TAG "ui_epaper"
#define WINDOW_SCALE 2
#define EPAPER_W_PX  250
#define EPAPER_H_PX  122

// User input pins
#define NUM_COMMANDS nav::Command_MAX-nav::Command_MIN
#define PIN_BUTTON_L 15
#define PIN_BUTTON_R 2
#define PIN_BUTTON_U 26
#define PIN_BUTTON_D 13
#define PIN_BUTTON_E 0

// EPD display pins
#define PIN_CS 14
#define PIN_DC 27
#define PIN_RST 33
#define PIN_BUSY -1 // no busy pin, and fooling the hardware is device-dependent

// Buzzer output
#define BUZZ_MILLIS 75
#define BUZZ_NOTIFY_MILLIS 500
#define PIN_BUZZER 25

class UIEPaper : public UI {
public:
  UIEPaper();
  Command nextCommand();
  void clear();
  void drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation);
  void drawText(const std::string& text, const int& size, const int& x, const int& y);
  void drawShape(const std::vector<std::pair<int, int>>& points);
  void partialUpdate();
  void fullUpdate();
  void loop();
  bool isOpen();
  void setFont(const FONT_T* f);
  void setRotation(int r);
  void getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h);
  void DrawSidebarText(std::string text, bool leftside);
  void alertThePlayer();

private:
  GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display;
  void DrawNametagScreen(
      std::string firstname,
      std::string lastname,
      std::string username,
      std::string site);

  void DrawStringAt(
      std::string s,           // string to draw
      int x, int y,            // where to draw.
      int* xmax, int* ymax     // where to store bottom right coords of bounds
      );
  bool buzzerLoop();
  // Debounce button presses
  bool prevStates[nav::Command_MAX-nav::Command_MIN];
  uint64_t buzzEnd;
};

#endif // UI_EPAPER_H
#endif // UI_EPAPER
