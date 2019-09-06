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

// draw text at a given location (x,y of top left corner) in the current font
void UIEPaper::DrawStringAt(
    std::string s,           // string to draw
    int x, int y,            // where to draw.
    int* xmax, int* ymax     // where to store bottom right coords of bounds
    ) {
  int16_t xx, yy;
  uint16_t ww, hh;
  display.getTextBounds(s.c_str(), x, y, &xx, &yy, &ww, &hh);
  display.setCursor(x, y+hh);
  // TODO - blank bounding rect?
  display.print(s.c_str());

  if (xmax) {
    *xmax = x + ww;
  }

  if (ymax) {
    *ymax = y+hh;;
  }
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

  const GFXfont* f = PickBestFontForString(s, maxw, fonts);
  display.setFont(f);
  DrawStringAt(s, x, y, xmax, ymax);
}



void UIEPaper::DrawNametagScreen(
    std::string firstname,
    std::string lastname,
    std::string username,
    std::string site) {

  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(ROTATION_NAMETAG);

  DrawSidebarText("press any key to play", true);

  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;;
  int y_offset = NAMETAG_TOP_MARGIN;

  DrawStringWithin(
      firstname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  LINESPACING;

  DrawStringWithin(
      lastname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  2*LINESPACING;

  display.setFont(&RobotoMonoBold6pt7b);
  DrawStringAt(
      username,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  display.setFont(&RobotoMonoBold6pt7b);
  DrawStringAt(
      site,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

}

void UIEPaper::DrawSidebarText(std::string text, bool leftside) {
  int16_t rotation = display.getRotation();
  if (leftside) {
    display.setRotation(ROTATION_GAME_LEFTSIDE);
  } else {
    display.setRotation(ROTATION_GAME_RIGHTSIDE);
  }
  display.setFont(&Org_01);
  display.fillRect(0, 0, EPAPER_SHORT_DIMENSION, SIDEBAR_WIDTH, GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(9, 9);
  display.print(text.c_str());

  // clean up
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(rotation);
}


// magic values are SPI pin numbers for d32 pro shield
UIEPaper::UIEPaper() : display(GxEPD2_213_B72(14, 27, 33, -1)) {
  // set up the display
	display.init(115200);
  display.setTextColor(GxEPD_BLACK);
  display.setTextWrap(false);
  display.mirror(0);

  // full window mode is the initial mode, set it anyway
  display.setFullWindow();

  display.fillScreen(GxEPD_WHITE);
  DrawNametagScreen(
      "Jeff",
      "Cooper",
      "jeffcooper@", 
      "US-PIT");
  display.display(false); // do a full update
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
  //display.fillScreen(GxEPD_WHITE);
  //display.display(false);
}

bool UIEPaper::flush() {
  // TODO
  return true;
}

void UIEPaper::drawText(const std::string& text, const int& size, const int& x, const int& y) {
  // dont' use windowed updates. we don't need to.
  display.setCursor(x, y); // set the postition to start printing text
  display.print(text.c_str()); // print some text
  display.display(true);
}

void UIEPaper::drawShape(const std::vector<std::pair<int, int>>& points) {
  // TODO
}

void UIEPaper::drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y) {
  // TODO
}

#endif // UI_EPAPER
