#ifdef UI_EPAPER

#include "ui_epaper.h"
#include "GxEPD2_BW.h"
#include <Fonts/Org_01.h>
#include <gfxfont.h>

#include "fonts.h"

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
    const FONT_T* const fonts[] // fonts to pick from
    ) {

  const FONT_T* f = PickBestFontForString(s, maxw, fonts);
  setFont(f);
  DrawStringAt(s, x, y, xmax, ymax);
}



void UIEPaper::DrawNametagScreen(
    std::string firstname,
    std::string lastname,
    std::string username,
    std::string site) {

  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  setRotation(ROTATION_NAMETAG);

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

  setFont(&RobotoMonoBold6pt7b);
  DrawStringAt(
      username,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  setFont(&RobotoMonoBold6pt7b);
  DrawStringAt(
      site,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

}

void UIEPaper::setRotation(int r) {
  display.setRotation(r);
}

void UIEPaper::DrawSidebarText(std::string text, bool leftside) {
  int16_t rotation = display.getRotation();
  if (leftside) {
    setRotation(ROTATION_GAME_LEFTSIDE);
  } else {
    setRotation(ROTATION_GAME_RIGHTSIDE);
  }
  setFont(&Org_01);
  display.fillRect(0, 0, EPAPER_SHORT_DIMENSION, SIDEBAR_WIDTH, GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(9, 9);
  display.print(text.c_str());

  // clean up
  display.setTextColor(GxEPD_BLACK);
  setRotation(rotation);
}


// magic values are SPI pin numbers for d32 pro shield
UIEPaper::UIEPaper() : display(GxEPD2_213_B72(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY)) {
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

  pinMode(PIN_BUTTON_L, INPUT_PULLUP);
  pinMode(PIN_BUTTON_R, INPUT_PULLUP);
  pinMode(PIN_BUTTON_U, INPUT_PULLUP);
  pinMode(PIN_BUTTON_D, INPUT_PULLUP);
  pinMode(PIN_BUTTON_E, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  // Always non-busy, so as not to block
  pinMode(PIN_BUSY, OUTPUT);
  digitalWrite(PIN_BUSY, HIGH);

  buzzStart = 0;
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

  // Handle button commands
  // States are in order of enum defined in nav.fbs
  // Note that enum 0 is "Command_unknown" so indexes are offset by 1
  bool states[NUM_COMMANDS] = {
    !digitalRead(PIN_BUTTON_D),
    !digitalRead(PIN_BUTTON_U),
    !digitalRead(PIN_BUTTON_L),
    !digitalRead(PIN_BUTTON_R),
    !digitalRead(PIN_BUTTON_E)
  };
  auto result = nav::Command_unknown;
  for (int i = 0; i < NUM_COMMANDS; i++) {
    if (!prevStates[i] && states[i]) { // On rising edge
      result = (nav::Command) (i+1);
      break;
    }
  }
  memcpy(prevStates, states, NUM_COMMANDS);

  if (result != nav::Command_unknown) {
    buzzStart = millis();
    digitalWrite(PIN_BUZZER, HIGH);
  }

  return result;
}

void UIEPaper::clear() {
  display.fillScreen(GxEPD_WHITE);
}

void UIEPaper::partialUpdate() {
  display.display(true);
}

void UIEPaper::fullUpdate() {
  while(!buzzerLoop()){};
  display.display(false);
}

void UIEPaper::setFont(const FONT_T* f) {
  display.setFont(f);
}

void UIEPaper::getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h) {
  int16_t xx, yy;
  uint16_t ww, hh;
  display.getTextBounds(s.c_str(), 0, 0, &xx, &yy, &ww, &hh);
  *xmin = xx;
  *ymin = yy;
  *w = ww;
  *h = hh;
}

// return true when the buzzer is done buzzing
bool UIEPaper::buzzerLoop() {
  if (buzzStart == 0) {
    return true;
  }

  const auto now = millis();
  if (now > buzzStart + BUZZ_MILLIS) {
    buzzStart = 0;
    digitalWrite(PIN_BUZZER, LOW);
    return true;
  }

  return false;
}

void UIEPaper::loop() {
  buzzerLoop();
};
bool UIEPaper::isOpen() { return true; };

void UIEPaper::drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation) {
  // dont' use windowed updates. we don't need to.
  display.setCursor(x, y); // set the postition to start printing text
  display.print(text.c_str()); // print some text
}

void UIEPaper::drawShape(const std::vector<std::pair<int, int>>& points) {
  // TODO
}

void UIEPaper::drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y) {
  // TODO
}

#endif // UI_EPAPER
