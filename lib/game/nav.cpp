#include "nav.h"

// <Page, std::map<Command, Page>>
// Values must be in order of the Page and Command enums defined
// in /proto.
static const int NAV_STATE_TRANSITION[Page_MAX][Command_MAX] = {
  { // Page_main,
    Page_fleetEntry, // Command_down
    Page_launchEntry, // Command_up
    Page_noOp, // Command_left
    Page_tradeEntry, // Command_right
    Page_settingsEntry // Command_enter
  },
  { // Page_settingsEntry,
    Page_settingsSelectUser, // Command_down
    Page_settingsReset, // Command_up
    Page_main, // Command_left
    Page_settingsChangeName, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_tradeEntry,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_main, // Command_left
    Page_noOp, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_fleetEntry,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_main, // Command_left
    Page_noOp, // Command_right
    Page_shipDetails // Command_enter
  },
  { // Page_launchEntry,
    Page_main, // Command_down
    Page_main, // Command_up
    Page_main, // Command_left
    Page_main, // Command_right
    Page_launchSplash // Command_enter
  },
  { // Page_settingsChangeName,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_settingsEntry // Command_enter
  },
  { // Page_settingsSelectUser,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_settingsEntry, // Command_left
    Page_noOp, // Command_right
    Page_main // Command_enter
  },
  { // Page_settingsReset,
    Page_main, // Command_down
    Page_main, // Command_up
    Page_main, // Command_left
    Page_main, // Command_right
    Page_main // Command_enter
  },
  { // Page_shipDetails,
    Page_shipRename, // Command_down
    Page_noOp, // Command_up
    Page_fleetEntry, // Command_left
    Page_shipMissionSelect, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_shipMissionSelect,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_shipDetails, // Command_left
    Page_shipDestSelect, // Command_right
    Page_shipDestSelect // Command_enter
  },
  { // Page_shipDestSelect,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_shipMissionSelect, // Command_left
    Page_shipConfirm, // Command_right
    Page_shipConfirm // Command_enter
  },
  { // Page_shipConfirm,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_shipDestSelect, // Command_left
    Page_shipSplash, // Command_right
    Page_shipSplash // Command_enter
  },
  { // Page_shipSplash,
    Page_fleetEntry, // Command_down
    Page_fleetEntry, // Command_up
    Page_fleetEntry, // Command_left
    Page_fleetEntry, // Command_right
    Page_fleetEntry // Command_enter
  },
  { // Page_shipRename,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_shipDetails // Command_enter
  },
  { // Page_eventShipVisit,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_eventPlayerLaunch,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_shipVisitDecision,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_shipVisitOutcome,
    Page_noOp, // Command_down
    Page_noOp, // Command_up
    Page_noOp, // Command_left
    Page_noOp, // Command_right
    Page_noOp // Command_enter
  },
  { // Page_launchSplash,
    Page_shipRename, // Command_down
    Page_shipRename, // Command_up
    Page_shipRename, // Command_left
    Page_shipRename, // Command_right
    Page_shipRename // Command_enter
  }
};

nav::Page nextPage(const nav::Page& page, const nav::Command& cmd) {
  if (page == Page_noOp) {
    return Page_noOp;
  }
  // CMD is offset by 1 due to Command_unknown
  return (nav::Page) (NAV_STATE_TRANSITION[(int)page][((int)cmd)-1]);
}
