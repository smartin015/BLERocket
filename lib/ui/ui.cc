#include "ui.h"
#include <iostream>
#include "nav.h"

void UI::drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center) {
  drawText("^ " + top, SZ_S, cx, cy);
  drawText("V " + bottom, SZ_S, cx, cy + SZ_M);
  drawText("< " + left, SZ_S, cx, cy + 2*SZ_M);
  drawText("> " + right, SZ_S, cx, cy + 3*SZ_M);
  drawText("X " + center, SZ_S, cx, cy + 4*SZ_M);
}

void UI::render(const Engine& engine) {
  const auto p = engine.getPage();
  drawControls(150, 5,
    engine.suppressNav(Command::UP) ? "" : enumStr(nextPage(p, Command::UP)),
    engine.suppressNav(Command::LEFT) ? "" : enumStr(nextPage(p, Command::LEFT)),
    engine.suppressNav(Command::DOWN) ? "" : enumStr(nextPage(p, Command::DOWN)),
    engine.suppressNav(Command::RIGHT) ? "" : enumStr(nextPage(p, Command::RIGHT)),
    engine.suppressNav(Command::ENTER) ? "" : enumStr(nextPage(p, Command::ENTER)));

  switch (p) {
    case nav::Page::MAIN:
      drawMain(engine);
      break;
    case nav::Page::SETTINGS_ENTRY:
      drawSettingsEntry(engine);
      break;
    case nav::Page::TRADE_ENTRY:
      drawTradeEntry(engine);
      break;
    case nav::Page::FLEET_ENTRY:
      drawFleetEntry(engine);
      break;
    case nav::Page::LAUNCH_ENTRY:
      drawLaunchEntry(engine);
      break;
    case nav::Page::SETTINGS_CHANGE_NAME:
      drawSettingsChangeName(engine);
      break;
    case nav::Page::SETTINGS_SELECT_USER:
      drawSettingsSelectUser(engine);
      break;
    case nav::Page::SETTINGS_RESET:
      drawSettingsReset(engine);
      break;
    case nav::Page::SHIP_DETAILS:
      drawShipDetails(engine);
      break;
    case nav::Page::SHIP_MISSION_SELECT:
      drawShipMissionSelect(engine);
      break;
    case nav::Page::SHIP_DEST_SELECT:
      drawShipDestSelect(engine);
      break;
    case nav::Page::SHIP_CONFIRM:
      drawShipConfirm(engine);
      break;
    case nav::Page::SHIP_SPLASH:
      drawShipSplash(engine);
      break;
    case nav::Page::SHIP_RENAME:
      drawShipRename(engine);
      break;
    case nav::Page::EVENT_SHIP_VISIT:
      drawEventShipVisit(engine);
      break;
    case nav::Page::EVENT_PLAYER_LAUNCH:
      drawEventPlayerLaunch(engine);
      break;
    case nav::Page::SHIP_VISIT_DECISION:
      drawShipVisitDecision(engine);
      break;
    case nav::Page::SHIP_VISIT_OUTCOME:
      drawShipVisitOutcome(engine);
      break;
    case nav::Page::LAUNCH_SPLASH:
      drawLaunchSplash(engine);
      break;
    default:
      // TODO show error page
      break;
  }
}
