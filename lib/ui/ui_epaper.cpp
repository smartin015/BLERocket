#ifdef UI_EPAPER

#include "ui_epaper.h"
#include "GxEPD2_BW.h"
#include <Fonts/Org_01.h>
#include <gfxfont.h>


#include "fonts/PoppinsExtraBold18pt7b.h"
#include "fonts/PoppinsExtraBold16pt7b.h"
#include "fonts/PoppinsExtraBold12pt7b.h"
#include "fonts/PoppinsExtraBold8pt7b.h"

#include "fonts/RobotoMonoBold6pt7b.h"
#include "fonts/RobotoMonoBold12pt7b.h"
#include "fonts/RobotoMonoBold14pt7b.h"


static std::string first_name = "";
static std::string last_name = "";

static const GFXfont* const KNOWN_FONTS_DISPLAY[] = {
  &PoppinsExtraBold18pt7b,
  &PoppinsExtraBold16pt7b,
  &PoppinsExtraBold12pt7b,
  &PoppinsExtraBold8pt7b,
  NULL,
};

const GFXfont* UIEPaper::PickBestFontForString(
    std::string s,                // the string to size
    int maxwidth,                 // the largest allowable width
    const GFXfont* const fonts[]  // the list of fonts to pick from
    ) {
  int max_width_found = -1;
  const GFXfont* font_fount = NULL;

  for (int i = 0; KNOWN_FONTS_DISPLAY[i] != NULL; i++) {
    int16_t xmin, ymin;
    uint16_t w, h;
    display.setFont(fonts[i]);
    display.getTextBounds(s.c_str(), 0, 0, &xmin, &ymin, &w, &h);
    int totalw = w - xmin;
    if (totalw - xmin > max_width_found  && totalw <= maxwidth) {
      max_width_found = w - xmin;
      font_fount = fonts[i];
    }
  }
  return font_fount;
}

// draw text as large as possible given a top-left corner (x,y) and a maximum
// width maxw. 
void UIEPaper::DrawStringWithin(
    std::string s,           // string to draw
    int x, int y,            // where to draw.
    int* xmax, int* ymax,    // where to store bottom right coords of bounds
    int maxw,                // maximum width for drawing
    const GFXfont* const fonts[] // fonts to pick from
    ) {
  const GFXfont* f = this->PickBestFontForString(s, maxw, fonts);
  this->display.setFont(f);
  int16_t xx, yy;
  uint16_t ww, hh;
  this->display.getTextBounds(s.c_str(), x, y, &xx, &yy, &ww, &hh);
  this->display.setCursor(x, y+hh);
  // TODO - blank bounding rect?
  this->display.print(s.c_str());

  if (xmax) {
    *xmax = x + ww;
  }

  if (ymax) {
    *ymax = y+hh;;
  }
}



void UIEPaper::DrawNametagScreen(
    std::string firstname,
    std::string lastname,
    std::string username,
    std::string site) {

  this->display.setFullWindow();
  this->display.fillScreen(GxEPD_WHITE);
  this->display.setRotation(ROTATION_NAMETAG);

  this->DrawSidebarText("Rockets n'at 0.1 beta", true);

  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;;
  int y_offset = 10;

  this->DrawStringWithin(
      firstname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  LINESPACING;

  this->DrawStringWithin(
      lastname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  LINESPACING;

}

void UIEPaper::DrawSidebarText(std::string text, bool leftside) {
  int16_t rotation = this->display.getRotation();
  if (leftside) {
    display.setRotation(ROTATION_GAME_LEFTSIDE);
  } else {
    display.setRotation(ROTATION_GAME_RIGHTSIDE);
  }
  this->display.fillRect(0, 0, EPAPER_SHORT_DIMENSION, SIDEBAR_WIDTH, GxEPD_BLACK);
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
  // disable text wrapping to avoid whackiness
  display.setTextWrap(false);

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

    this->DrawNametagScreen("Firstname", "reallylonglastname", "jeffcooper@", "US-PIT");


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
