#ifndef BLE_UI_H
#define BLE_UI_H

#include "engine.h"
#include "nav_generated.h"
#include <vector>
#include <time.h>

#include "fonts.h"

#define SZ_S 10
#define SZ_M 20
#define SZ_L 30

#define SIDEBAR_WIDTH 15
#define SIDEBAR_MARGIN 15

#define NAMETAG_TOP_MARGIN 15
#define LINESPACING 5

#define EPAPER_LONG_DIMENSION 250
#define EPAPER_SHORT_DIMENSION 122

#define BODY_X 10
#define BODY_Y 40

#define NOTIFY_X 10
#define NOTIFY_Y 100

#define TITLE_SZ 18
#define TITLE_X 15
#define TITLE_Y 15

#define NOTIFY_DURATION_SECONDS 5

#define SELECTOR_NUM_ITEMS 5

// these are used for setting the "game mode" (flip screen over for nametag vs
// play. Numbers correspond to gxepd rotations.
#define ROTATION_GAME 3
#define ROTATION_NAMETAG 1

// these are used internally.
#define ROTATION_GAME_LEFTSIDE 0
#define ROTATION_GAME_RIGHTSIDE 2
#define ROTATION_NAMETAG_RIGHTSIDE 0
#define ROTATION_NAMETAG_LEFTSIDE 2

class UI {
public:
  UI() : notify_start(0) {}

  void render(Engine* engine);
  virtual Command nextCommand() = 0;

  // blank the buffer
  virtual void clear() = 0;

  // do any maintenance required for the output (eg redraw on native)
  virtual void loop() = 0;

  // do a full update of the screen
  virtual void fullUpdate() = 0;

  // do a partial update of the screen
  virtual void partialUpdate() = 0;

  // whether the UI has been closed
  virtual bool isOpen() = 0;

  // set screen rotation
  virtual void setRotation(int r) = 0;

  // TODO - temporary while I refactor UI code
  void drawText(const std::string& text, const int& size, const int& x, const int& y);

protected:
  // draw text at a given location on the screen, with a given orientation.
  // pixels are given relative to specified orientation
  virtual void drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation) = 0;

  // TODO
  virtual void drawShape(const std::vector<std::pair<int, int>>& points) = 0;

  void drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y);

  // set the working font
  virtual void setFont(const FONT_T* f) = 0;

  // get the bounds of a text using the currently set font
  virtual void getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h) = 0;

  const FONT_T* PickBestFontForString(
      std::string s,                // the string to size
      int maxwidth,                 // the largest allowable width
      const FONT_T* const fonts[]   // the list of fonts to pick from
      );

  virtual void DrawStringAt(
      std::string s,           // string to draw
      int x, int y,            // where to draw.
      int* xmax, int* ymax     // where to store bottom right coords of bounds
      ) = 0;

  void DrawStringWithin(
      std::string s,           // string to draw
      int x, int y,            // where to draw.
      int* xmax, int* ymax,    // where to store bottom right coords of bounds
      int maxw,                // maximum width for drawing
      const FONT_T* const fonts[] // fonts to pick from
      );
  virtual void DrawSidebarText(std::string s, bool leftside) = 0;

  // alert the player of an event
  virtual void alertThePlayer() = 0;

  std::string notification;

private:
  nav::Page lastRenderedPage;
  time_t notify_start;
  void handleNotification(const std::string& text);
  void persistNotification();

  void drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center);

  // Individual page render functions in ./ui/pages
  void drawMain(const Engine* engine);
  void drawNametag(const Engine* engine);
  void drawSettingsEntry(const Engine* engine);
  void drawTradeEntry(const Engine* engine);
  void drawFleetEntry(const Engine* engine);
  void drawLaunchEntry(const Engine* engine);
  void drawSettingsSelectUser(const Engine* engine);
  void drawSettingsReset(const Engine* engine);
  void drawShipDetails(const Engine* engine);
  void drawMissionTypeSelect(const Engine* engine);
  void drawMissionDestSelect(const Engine* engine);
  void drawMissionConfirm(const Engine* engine);
  void drawMissionSplash(const Engine* engine);
  void drawShipRename(const Engine* engine);
  void drawShipVisitEntry(const Engine* engine);
  void drawShipVisitDecision(const Engine* engine);
  void drawShipVisitOutcome(const Engine* engine);
  void drawLaunchSplash(const Engine* engine);
};

#endif // BLE_UI_H
