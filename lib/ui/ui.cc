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
    engine.suppressNav(nav::Command_up) ? "" : EnumNamePage(nextPage(p, nav::Command_up)),
    engine.suppressNav(nav::Command_left) ? "" : EnumNamePage(nextPage(p, nav::Command_left)),
    engine.suppressNav(nav::Command_down) ? "" : EnumNamePage(nextPage(p, nav::Command_down)),
    engine.suppressNav(nav::Command_right) ? "" : EnumNamePage(nextPage(p, nav::Command_right)),
    engine.suppressNav(nav::Command_enter) ? "" : EnumNamePage(nextPage(p, nav::Command_enter)));

  switch (p) {
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
    case nav::Page_settingsChangeName:
      drawSettingsChangeName(engine);
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
    case nav::Page_shipMissionSelect:
      drawShipMissionSelect(engine);
      break;
    case nav::Page_shipDestSelect:
      drawShipDestSelect(engine);
      break;
    case nav::Page_shipConfirm:
      drawShipConfirm(engine);
      break;
    case nav::Page_shipSplash:
      drawShipSplash(engine);
      break;
    case nav::Page_shipRename:
      drawShipRename(engine);
      break;
    case nav::Page_eventShipVisit:
      drawEventShipVisit(engine);
      break;
    case nav::Page_eventPlayerLaunch:
      drawEventPlayerLaunch(engine);
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
}
