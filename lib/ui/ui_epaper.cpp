#ifdef UI_EPAPER

#include "ui_epaper.h"
#include "GxEPD2_BW.h"
#include <Fonts/Org_01.h>
#include "fonts/PoppinsExtraBold18pt7b.h"
#include "fonts/RobotoMonoBold6pt7b.h"

#define ROTATION_GAME 3
#define ROTATION_NAMETAG 1
#define ROTATION_GAME_LEFTSIDE 0
#define ROTATION_GAME_RIGHTSIDE 2

static std::string first_name = "";
static std::string last_name = "";

void UIEPaper::DrawNametagScreen() {
  this->display.setFullWindow();
  this->display.fillScreen(GxEPD_WHITE);
  this->display.setRotation(ROTATION_NAMETAG);
}

void UIEPaper::DrawSidebarText(std::string text, bool leftside) {
  int16_t rotation = this->display.getRotation();
  if (leftside) {
    display.setRotation(ROTATION_GAME_LEFTSIDE);
  } else {
    display.setRotation(ROTATION_GAME_RIGHTSIDE);
  }
  this->display.fillRect(0, 0, 122, 15, GxEPD_BLACK);
  this->display.setTextColor(GxEPD_WHITE);
  this->display.setCursor(10, 10);
  this->display.setFont(&Org_01);
  this->display.print(text.c_str());

  // clean up
  this->display.setTextColor(GxEPD_BLACK);
  this->display.setRotation(rotation);
}


UIEPaper::UIEPaper() : display(GxEPD2_213_B72(14, 27, 33, -1)) {
	display.init(115200);
  // TODO
  //Serial.println("helloWorld");
  const char text[] = "Hello World!";
  // most e-papers have width < height (portrait) as native orientation, especially the small ones
  // in GxEPD2 rotation 0 is used for native orientation (most TFT libraries use 0 fix for portrait orientation)
  // set rotation to 1 (rotate right 90 degrees) to have enough space on small displays (landscape)
  display.setRotation(ROTATION_GAME);
  // select a suitable font in Adafruit_GFX
  display.setFont(&Org_01);
  // on e-papers black on white is more pleasant to read
  display.setTextColor(GxEPD_BLACK);
  // Adafruit_GFX has a handy method getTextBounds() to determine the boundary box for a text for the actual font
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  // full window mode is the initial mode, set it anyway
  display.setFullWindow();

  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
  display.setCursor(x, y); // set the postition to start printing text

  display.mirror(0);

  // here we use paged drawing, even if the processor has enough RAM for full buffer
  // so this can be used with any supported processor board.
  // the cost in code overhead and execution time penalty is marginal
  // tell the graphics class to use paged drawing mode
  display.firstPage();
  do
  {
    // this part of code is executed multiple times, as many as needed,
    // in case of full buffer it is executed once
    // IMPORTANT: each iteration needs to draw the same, to avoid strange effects
    // use a copy of values that might change, don't read e.g. from analog or pins in the loop!
    // display.
    display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
    
    display.setRotation(ROTATION_NAMETAG);
    display.setFont(&PoppinsExtraBold18pt7b);
    display.setCursor(30, 40);
    display.print("JEFF");
    display.setCursor(30, 70);
    display.print("COOPER");
    display.setCursor(30, 90);
    display.setFont(&RobotoMonoBold6pt7b);
    display.print("jeffcooper@");
    display.setCursor(30, 110);
    display.print("US-PIT");

    this->DrawSidebarText("Rockets n'at 0.1 beta", true);

    // end of part executed multiple times
  }
  // tell the graphics class to transfer the buffer content (page) to the controller buffer
  // the graphics class will command the controller to refresh to the screen when the last page has been transferred
  // returns true if more pages need be drawn and transferred
  // returns false if the last page has been transferred and the screen refreshed for panels without fast partial update
  // returns false for panels with fast partial update when the controller buffer has been written once more, to make the differential buffers equal
  // (for full buffered with fast partial update the (full) buffer is just transferred again, and false returned)
  while (display.nextPage());
}

Command UIEPaper::nextCommand() {
  // Handle serial commands
  if (Serial.available()) {
    char c = Serial.read();
    ESP_LOGI(UI_TAG, "Parsing serial %c", c);
    switch (c) {
      case 'w':
        return nav::Command_up;
        break;
      case 'a':
        return nav::Command_left;
        break;
      case 's':
        return nav::Command_down;
        break;
      case 'd':
        return nav::Command_right;
        break;
      case 'e':
        return nav::Command_enter;
        break;
      default:
        break;
    }
  }

  // TODO handle button commands
  return nav::Command_unknown;
}

void UIEPaper::clear() {
  // TODO
}

bool UIEPaper::flush() {
  // TODO
  return true;
}

void UIEPaper::drawText(const std::string& text, const int& size, const int& x, const int& y) {
 // int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
 // display.getTextBounds(text.c_str(), (uint16_t)x, (uint16_t)y, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
 // // center bounding box by transposition of origin:
 // uint16_t cx = ((display.width() - tbw) / 2) - tbx;
 // uint16_t cy = ((display.height() - tbh) / 2) - tby;

  display.setPartialWindow(0, 0, display.width(), display.height());

  do {
    display.setCursor(x, y); // set the postition to start printing text
    display.print(text.c_str()); // print some text
  } while (display.nextPage());

 // TODO
}

void UIEPaper::drawShape(const std::vector<std::pair<int, int>>& points) {
  // TODO
}

void UIEPaper::drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y) {
  // TODO
}

#endif // UI_EPAPER
