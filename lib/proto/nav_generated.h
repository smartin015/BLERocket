// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_NAV_NAV_H_
#define FLATBUFFERS_GENERATED_NAV_NAV_H_

#include "flatbuffers/flatbuffers.h"

namespace nav {

enum Command {
  Command_unknown = 0,
  Command_down = 1,
  Command_up = 2,
  Command_left = 3,
  Command_right = 4,
  Command_enter = 5,
  Command_MIN = Command_unknown,
  Command_MAX = Command_enter
};

inline const Command (&EnumValuesCommand())[6] {
  static const Command values[] = {
    Command_unknown,
    Command_down,
    Command_up,
    Command_left,
    Command_right,
    Command_enter
  };
  return values;
}

inline const char * const *EnumNamesCommand() {
  static const char * const names[] = {
    "unknown",
    "down",
    "up",
    "left",
    "right",
    "enter",
    nullptr
  };
  return names;
}

inline const char *EnumNameCommand(Command e) {
  if (e < Command_unknown || e > Command_enter) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesCommand()[index];
}

enum Page {
  Page_main = 0,
  Page_settingsEntry = 1,
  Page_tradeEntry = 2,
  Page_fleetEntry = 3,
  Page_launchEntry = 4,
  Page_settingsSelectUser = 5,
  Page_settingsReset = 6,
  Page_shipDetails = 7,
  Page_missionTypeSelect = 8,
  Page_missionDestSelect = 9,
  Page_missionConfirm = 10,
  Page_missionSplash = 11,
  Page_shipRename = 12,
  Page_shipVisitEntry = 13,
  Page_shipVisitDecision = 14,
  Page_shipVisitOutcome = 15,
  Page_launchSplash = 16,
  Page_noOp = 17,
  Page_nametag = 18,
  Page_MIN = Page_main,
  Page_MAX = Page_nametag
};

inline const Page (&EnumValuesPage())[19] {
  static const Page values[] = {
    Page_main,
    Page_settingsEntry,
    Page_tradeEntry,
    Page_fleetEntry,
    Page_launchEntry,
    Page_settingsSelectUser,
    Page_settingsReset,
    Page_shipDetails,
    Page_missionTypeSelect,
    Page_missionDestSelect,
    Page_missionConfirm,
    Page_missionSplash,
    Page_shipRename,
    Page_shipVisitEntry,
    Page_shipVisitDecision,
    Page_shipVisitOutcome,
    Page_launchSplash,
    Page_noOp,
    Page_nametag
  };
  return values;
}

inline const char * const *EnumNamesPage() {
  static const char * const names[] = {
    "main",
    "settingsEntry",
    "tradeEntry",
    "fleetEntry",
    "launchEntry",
    "settingsSelectUser",
    "settingsReset",
    "shipDetails",
    "missionTypeSelect",
    "missionDestSelect",
    "missionConfirm",
    "missionSplash",
    "shipRename",
    "shipVisitEntry",
    "shipVisitDecision",
    "shipVisitOutcome",
    "launchSplash",
    "noOp",
    "nametag",
    nullptr
  };
  return names;
}

inline const char *EnumNamePage(Page e) {
  if (e < Page_main || e > Page_nametag) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesPage()[index];
}

}  // namespace nav

#endif  // FLATBUFFERS_GENERATED_NAV_NAV_H_
