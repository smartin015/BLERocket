#include "ui.h"

#define SZ_S 10
#define SZ_M 20
#define SZ_L 30

#include <capnp/schema.h>
#include "nav.h"

template <class T> std::string enumStr(T e) {
  auto x = capnp::Schema::from<T>();
  return x.asEnum().getEnumerants()[(int)e].getProto().getName().cStr();
}


void UI::drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center) {
  drawText("^ " + top, SZ_S, cx, cy);
  drawText("V " + bottom, SZ_S, cx, cy + SZ_M);
  drawText("< " + left, SZ_S, cx, cy + 2*SZ_M);
  drawText("> " + right, SZ_S, cx, cy + 3*SZ_M);
  drawText("X " + center, SZ_S, cx, cy + 4*SZ_M);
}

void UI::render(const Engine& engine) {
  auto nTop = nextPage(engine.getPage(), Command::UP);
  auto nBot = nextPage(engine.getPage(), Command::DOWN);
  auto nLft = nextPage(engine.getPage(), Command::LEFT);
  auto nRht = nextPage(engine.getPage(), Command::RIGHT);
  auto nCtr = nextPage(engine.getPage(), Command::ENTER);
  drawControls(150, 5,
    enumStr(nTop),
    enumStr(nLft),
    enumStr(nBot),
    enumStr(nRht),
    enumStr(nCtr));

  switch (engine.getPage()) {
    case nav::Page::MAIN:
      drawText("MAIN", 18, 15, 15);
      break;
    case nav::Page::SETTINGS_ENTRY:
      drawText("SETTINGS_ENTRY", 18, 15, 15);
      break;
    case nav::Page::TRADE_ENTRY:
      drawText("TRADE_ENTRY", 18, 15, 15);
      break;
    case nav::Page::FLEET_ENTRY:
      drawText("FLEET_ENTRY", 18, 15, 15);
      break;
    case nav::Page::LAUNCH_ENTRY:
      drawText("LAUNCH_ENTRY", 18, 15, 15);
      break;
    case nav::Page::SETTINGS_CHANGE_NAME:
      drawText("SETTINGS_CHANGE_NAME", 18, 15, 15);
      break;
    case nav::Page::SETTINGS_SELECT_USER:
      drawText("SETTINGS_SELECT_USER", 18, 15, 15);
      break;
    case nav::Page::SETTINGS_RESET:
      drawText("SETTINGS_RESET", 18, 15, 15);
      break;
    case nav::Page::SHIP_DETAILS:
      drawText("SHIP_DETAILS", 18, 15, 15);
      break;
    case nav::Page::SHIP_MISSION_SELECT:
      drawText("SHIP_MISSION_SELECT", 18, 15, 15);
      break;
    case nav::Page::SHIP_DEST_SELECT:
      drawText("SHIP_DEST_SELECT", 18, 15, 15);
      break;
    case nav::Page::SHIP_CONFIRM:
      drawText("SHIP_CONFIRM", 18, 15, 15);
      break;
    case nav::Page::SHIP_SPLASH:
      drawText("SHIP_SPLASH", 18, 15, 15);
      break;
    case nav::Page::SHIP_RENAME:
      drawText("SHIP_RENAME", 18, 15, 15);
      break;
    case nav::Page::EVENT_SHIP_VISIT:
      drawText("EVENT_SHIP_VISIT", 18, 15, 15);
      break;
    case nav::Page::EVENT_PLAYER_LAUNCH:
      drawText("EVENT_PLAYER_LAUNCH", 18, 15, 15);
      break;
    case nav::Page::SHIP_VISIT_DECISION:
      drawText("SHIP_VISIT_DECISION", 18, 15, 15);
      break;
    case nav::Page::SHIP_VISIT_OUTCOME:
      drawText("SHIP_VISIT_OUTCOME", 18, 15, 15);
      break;
    case nav::Page::LAUNCH_SPLASH:
      drawText("LAUNCH_SPLASH", 18, 15, 15);
      break;
    case nav::Page::NO_OP:
      drawText("NO_OP", 18, 15, 15);
      break;
    default:
      break;
  }
}
