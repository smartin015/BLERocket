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

std::string UI::getTitle(const Page& page) {
  switch (page) {
    case nav::Page::MAIN:
      return "ROCKETS N'AT";
    case nav::Page::SETTINGS_ENTRY:
      return "Settings";
    case nav::Page::TRADE_ENTRY:
      return "Trade";
    case nav::Page::FLEET_ENTRY:
      return "Fleet";
    case nav::Page::LAUNCH_ENTRY:
      return "3...2...1...";
    case nav::Page::SETTINGS_CHANGE_NAME:
      return "Change Name";
    case nav::Page::SETTINGS_SELECT_USER:
      return "Sel User";
    case nav::Page::SETTINGS_RESET:
      return "Reset?";
    case nav::Page::SHIP_DETAILS:
      return "Details";
    case nav::Page::SHIP_MISSION_SELECT:
      return "Mission";
    case nav::Page::SHIP_DEST_SELECT:
      return "Target";
    case nav::Page::SHIP_CONFIRM:
      return "Y/N?";
    case nav::Page::SHIP_SPLASH:
      return "Launched!";
    case nav::Page::SHIP_RENAME:
      return "Rename";
    case nav::Page::EVENT_SHIP_VISIT:
      return "Visitor!";
    case nav::Page::EVENT_PLAYER_LAUNCH:
      return "Player launched!";
    case nav::Page::SHIP_VISIT_DECISION:
      return "Decide...";
    case nav::Page::SHIP_VISIT_OUTCOME:
      return "Result";
    case nav::Page::LAUNCH_SPLASH:
      return "BLAST OFF!";
    case nav::Page::NO_OP:
      return "NO_OP";
    default:
      return "UNKNOWN";
  }
}

void UI::render(const Engine& engine) {
  auto p = engine.getPage();
  auto nTop = nextPage(p, Command::UP);
  auto nBot = nextPage(p, Command::DOWN);
  auto nLft = nextPage(p, Command::LEFT);
  auto nRht = nextPage(p, Command::RIGHT);
  auto nCtr = nextPage(p, Command::ENTER);
  drawControls(150, 5,
    enumStr(nTop),
    enumStr(nLft),
    enumStr(nBot),
    enumStr(nRht),
    enumStr(nCtr));
  auto title = getTitle(p);
  drawText(title, 18, 15, 15);
}
