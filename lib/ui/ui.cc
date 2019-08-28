#include "ui.h"

#define SZ_S 10
#define SZ_M 20
#define SZ_L 30

#define BODY_X 10
#define BODY_Y 40

#include <iostream>
#include <capnp/schema.h>
#include "nav.h"

template <class T> std::string enumStr(const T& e) {
  auto x = capnp::Schema::from<T>();
  auto es = x.asEnum().getEnumerants();
  if ((int)e > es.size()) {
    return "UNKNOWN";
  }
  return es[(int)e].getProto().getName().cStr();
}

void UI::drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center) {
  drawText("^ " + top, SZ_S, cx, cy);
  drawText("V " + bottom, SZ_S, cx, cy + SZ_M);
  drawText("< " + left, SZ_S, cx, cy + 2*SZ_M);
  drawText("> " + right, SZ_S, cx, cy + 3*SZ_M);
  drawText("X " + center, SZ_S, cx, cy + 4*SZ_M);
}

void UI::drawTradeEntry(const Engine& engine) {
  const auto& parts = engine.getParts();
  for (const auto& kv : parts) {
    if (kv.second == 0) {
      continue;
    }
    std::string text = enumStr((game::ShipPartType)kv.first);
    drawText(text + " " + std::to_string(kv.second), SZ_S,  BODY_X, BODY_Y + SZ_M*((uint8_t)kv.first));
  }
}

void UI::drawLaunchEntry(const Engine& engine) {
  const auto& parts = engine.getParts();
  for (const auto& kv : parts) {
    if (kv.second == 0) {
      drawText("Missing part " + enumStr(kv.first), SZ_S, BODY_X, BODY_Y);
      return;
    }
  }
  drawText("3...2...1...", SZ_S, BODY_X, BODY_Y);
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
      return "Launch";
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
  const auto p = engine.getPage();
  drawControls(150, 5,
    engine.suppressNav(Command::UP) ? "" : enumStr(nextPage(p, Command::UP)),
    engine.suppressNav(Command::LEFT) ? "" : enumStr(nextPage(p, Command::LEFT)),
    engine.suppressNav(Command::DOWN) ? "" : enumStr(nextPage(p, Command::DOWN)),
    engine.suppressNav(Command::RIGHT) ? "" : enumStr(nextPage(p, Command::RIGHT)),
    engine.suppressNav(Command::ENTER) ? "" : enumStr(nextPage(p, Command::ENTER)));
  drawText(getTitle(p), 18, 15, 15);

  switch (p) {
    case nav::Page::TRADE_ENTRY:
      drawTradeEntry(engine);
      break;
    case nav::Page::LAUNCH_ENTRY:
      drawLaunchEntry(engine);
      break;
    default:
      break;
  }
}
