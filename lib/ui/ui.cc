#include "ui.h"
#include <iostream>
#include "nav.h"

void UI::drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center) {
  //drawText("^ " + top, SZ_S, cx, cy);
  //drawText("V " + bottom, SZ_S, cx, cy + SZ_M);
  //drawText("< " + left, SZ_S, cx, cy + 2*SZ_M);
  //drawText("> " + right, SZ_S, cx, cy + 3*SZ_M);
  //drawText("X " + center, SZ_S, cx, cy + 4*SZ_M);

  std::cout << "^ " + top << std::endl;
  std::cout << "v " + bottom << std::endl;
  std::cout << "< " + left << std::endl;
  std::cout << "> " + right << std::endl;
  std::cout << "x " + center << std::endl;
}

void UI::handleNotification(const std::string& text) {
  notification = text;
  time(&notify_start);
}

void UI::persistNotification() {
  if (notification == "") {
    return;
  }

  time_t now = time(NULL);
  if (now - notify_start > NOTIFY_DURATION_SECONDS) {
    std::cout << "notification expired" << std::endl;
    notification = "";
    return;
  }

  //drawText(notification, SZ_S, NOTIFY_X, NOTIFY_Y);
}

void aRandomFunction(Engine* engine) {
  return;
}

// draw text as large as possible given a top-left corner (x,y) and a maximum
// width maxw.
void UI::DrawStringWithin(
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

void UI::render(Engine* engine) {
  clear();
  const auto p = engine->getPage();

  switch (p) {
    case nav::Page_nametag:
      drawNametag(engine);
      break;
    case nav::Page_main:
      drawMain(engine);
      break;
    case nav::Page_settingsEntry:
      drawSettingsEntry(engine);
      break;
    case nav::Page_tradeEntry:
      drawTradeEntry(engine);
      break;
    case nav::Page_fleetEntry:
      drawFleetEntry(engine);
      break;
    case nav::Page_launchEntry:
      drawLaunchEntry(engine);
      break;
    case nav::Page_settingsSelectUser:
      drawSettingsSelectUser(engine);
      break;
    case nav::Page_settingsReset:
      drawSettingsReset(engine);
      break;
    case nav::Page_shipDetails:
      drawShipDetails(engine);
      break;
    case nav::Page_missionTypeSelect:
      drawMissionTypeSelect(engine);
      break;
    case nav::Page_missionDestSelect:
      drawMissionDestSelect(engine);
      break;
    case nav::Page_missionConfirm:
      drawMissionConfirm(engine);
      break;
    case nav::Page_missionSplash:
      drawMissionSplash(engine);
      break;
    case nav::Page_shipRename:
      drawShipRename(engine);
      break;
    case nav::Page_shipVisitEntry:
      drawShipVisitEntry(engine);
      break;
    case nav::Page_shipVisitDecision:
      drawShipVisitDecision(engine);
      break;
    case nav::Page_shipVisitOutcome:
      drawShipVisitOutcome(engine);
      break;
    case nav::Page_launchSplash:
      drawLaunchSplash(engine);
      break;
    default:
      // TODO show error page
      break;
  }


  const auto* n = engine->getEvent();
  if (n->lastMessage > notify_start) {
    ESP_LOGI("UI", "Handling new message");
    handleNotification("Incoming transmission");
  }
  persistNotification();
  aRandomFunction(engine);

  // Page changed; trigger full update
  if (lastRenderedPage != p) {
    fullUpdate();
    lastRenderedPage = p;
    std::cout << "changed to page " << EnumNamePage(p) << std::endl;

    drawControls(150, 5,
      engine->suppressNav(nav::Command_up) ? "" : EnumNamePage(nextPage(p, nav::Command_up)),
      engine->suppressNav(nav::Command_left) ? "" : EnumNamePage(nextPage(p, nav::Command_left)),
      engine->suppressNav(nav::Command_down) ? "" : EnumNamePage(nextPage(p, nav::Command_down)),
      engine->suppressNav(nav::Command_right) ? "" : EnumNamePage(nextPage(p, nav::Command_right)),
      engine->suppressNav(nav::Command_enter) ? "" : EnumNamePage(nextPage(p, nav::Command_enter)));
  } else {
    partialUpdate();
  }
}
void UI::drawText(const std::string& text, const int& size, const int& x, const int& y) {
  drawText(text, size, x, y, 0);
}

void UI::drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y) {
  int x_offset = x;
  int y_offset = y;
    char buf[64];
  setFont(&FONT_ROBOTO_6);
  for (int i = 0; i < items.size(); i++) {
    snprintf(buf, sizeof(buf), "%s  %s", (i == selected ? "->" : "  "), items[i].c_str());
    DrawStringAt(
        buf,
        x_offset, y_offset,
        NULL, &y_offset);
  }
}


const FONT_T* UI::PickBestFontForString(
    std::string s,                // the string to size
    int maxwidth,                 // the largest allowable width
    const FONT_T* const fonts[]   // the list of fonts to pick from
    ) {
  int max_width_found = -1;
  const FONT_T* font_found = NULL;

  for (int i = 0; fonts[i] != NULL; i++) {
    int xmin, ymin, w, h;
    setFont(fonts[i]);
    getTextBounds(s, &xmin, &ymin, &w, &h);
    int totalw = w - xmin;
    if (totalw - xmin > max_width_found  && totalw <= maxwidth) {
      max_width_found = w - xmin;
      font_found = fonts[i];
    }
  }

  // Pick the smallest font
  if (font_found == NULL) {
    font_found = &FONT_TINY;
  }
  return font_found;
}

