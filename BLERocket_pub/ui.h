#ifndef BLE_UI_H
#define BLE_UI_H

/* msg format for shipry:
*  TYPE_RACE|ShipConfig
*  TYPE_TRADE|ShipConfig
*  TYPE_EXPLORE|ShipConfig
*  TYPE_SCORE|<uint32_t score>
* msg format for manufacturing:
*  TYPE_GIVE|ShipPart
*/

enum ui_t {
  // Default page for user (including the ever-important nametag)
  UI_MAIN = 0,

  // Entry points for user-triggered flows
  UI_SETTINGS_ENTRY = 1,
  UI_TRADE_ENTRY = 2,
  UI_FLEET_ENTRY = 3,
  UI_LAUNCH_ENTRY = 4,

  // Different game settings pages
  UI_SETTINGS_CHANGE_NAME = 5,
  UI_SETTINGS_SELECT_USER = 6,
  UI_SETTINGS_RESET = 7,

  // UI for acting on a single ship
  UI_SHIP_DETAILS = 8,
  UI_SHIP_MISSION_SELECT = 9,
  UI_SHIP_DEST_SELECT = 10,
  UI_SHIP_CONFIRM = 11,
  UI_SHIP_SPLASH = 12,
  UI_SHIP_RENAME = 13,

  // Events are arrive async from other users.
  // They are handled synchronously by the dest user.
  UI_EVENT_SHIP_VISIT = 14,
  UI_EVENT_PLAYER_LAUNCH = 15,

  // When user ships visit, the dest user is presented
  // with a random decision to make, and an outcome
  // following that decision.
  UI_SHIP_VISIT_DECISION = 16,
  UI_SHIP_VISIT_OUTCOME = 17,

  UI_LAUNCH_SPLASH = 18,

  UI_NUM = 19,
  UI_NULL = 20 // Use for non-valid nav commands
};

// User manual controls
enum cmd_t {
  CMD_DOWN = 0,
  CMD_UP = 1,
  CMD_LEFT = 2,
  CMD_RIGHT = 3,
  CMD_ENTER = 4,

  CMD_NUM = 5
};

// Note: NULL == 0, so the default case is to return to UI_MAIN
const uint8_t NAV_STATE_TRANSITION[UI_NUM][CMD_NUM] = {
  { // UI_MAIN
    UI_LAUNCH_ENTRY, // CMD_UP
    UI_FLEET_ENTRY, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_TRADE_ENTRY, // CMD_RIGHT
    UI_SETTINGS_ENTRY, // CMD_ENTER
  },
  { // UI_SETTINGS_ENTRY
    UI_SETTINGS_RESET, // CMD_UP
    UI_SETTINGS_SELECT_USER, // CMD_DOWN
    UI_MAIN, // CMD_LEFT
    UI_SETTINGS_CHANGE_NAME, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // UI_TRADE_ENTRY
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_MAIN, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // UI_FLEET_ENTRY
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_MAIN, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_SHIP_DETAILS, // CMD_ENTER
  },
  { // UI_LAUNCH_ENTRY
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_LAUNCH_SPLASH, // CMD_ENTER
  },
  { // TODO UI_SETTINGS_CHANGE_NAME
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SETTINGS_SELECT_USER
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SETTINGS_RESET
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_DETAILS
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_MISSION_SELECT
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_DEST_SELECT
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_CONFIRM
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_SPLASH
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_RENAME
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_EVENT_SHIP_VISIT
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_EVENT_PLAYER_LAUNCH
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_VISIT_DECISION
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_SHIP_VISIT_OUTCOME
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  },
  { // TODO UI_LAUNCH_SPLASH
    UI_NULL, // CMD_UP
    UI_NULL, // CMD_DOWN
    UI_NULL, // CMD_LEFT
    UI_NULL, // CMD_RIGHT
    UI_NULL, // CMD_ENTER
  }
};

#endif // BLE_UI_H
