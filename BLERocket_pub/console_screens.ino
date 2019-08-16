#include "ui.h"

void consoleRender(ui_t ui) {
  String needed;
  Serial.println("---");
  switch (ui) {
    case UI_MAIN:
//      Serial.println("Status");
//      Serial.println("Part (quality):");
//      for (int i = 0; i < NUM_PARTS; i++) {
//        if (parts[i] == 0) {
//          continue;
//        }
//        Serial.printf("%s (%d)\n", PART_NAMES[i], parts[i]);
//      }
//
//      if (num_ships > 0) {
//        Serial.println("Ships:");
//        for (int i = 0; i < num_ships; i++) {
//            Serial.printf("%d - cargo %d speed %d c %d d %d\n",
//              i,
//              ships[i].cargo,
//              ships[i].spd,
//              ships[i].c,
//              ships[i].d);
//        }
//      }
//      Serial.println("Commands: < CANCEL | v MAKE | > GIVE | ^ LAUNCH");
      break;
    case UI_SETTINGS_ENTRY:
      break;
    case UI_TRADE_ENTRY:
//      Serial.println("Make");
//      Serial.println(PART_NAMES[USER_PART]);
//      Serial.println("Commands: < BACK | X MAKE");
//      Serial.println("Give");
//      if (!giveTarget) {
//        Serial.println("Select part:");
//        for (int i = 0; i < NUM_PARTS; i++) {
//          if (parts[i] == 0) {
//            continue;
//          }
//          if (partSel == i) {
//            Serial.print("> ");
//          } else {
//            Serial.print("  ");
//          }
//          Serial.printf("%s (quality %d)\n", PART_NAMES[i], parts[i]);
//        }
//      } else {
//        Serial.println("Select target:");
//        for (int i = 0; i < num_dests; i++) {
//          if (destSel == i) {
//            Serial.print("> ");
//          } else {
//            Serial.print("  ");
//          }
//          Serial.printf("%d\n", dests[i]);
//        }
//      }
//      Serial.println("Commands: << BACK | >< DEST/PRT | ^v SEL | X GIVE");
      break;
    case UI_FLEET_ENTRY:
      break;
    case UI_LAUNCH_ENTRY:
//      Serial.println("Launch");
//      for (int i = 0; i < NUM_PARTS; i++) {
//        if (parts[i] == 0) {
//          needed += PART_NAMES[i];
//          needed += " ";
//        }
//      }
//      if (needed.length() > 0) {
//        Serial.printf("Still need: %s\n", needed);
//        Serial.println("Commands: << BACK");
//      } else {
//        Serial.println("Launch new ship with current parts?");
//        Serial.println("Commands: << BACK | X CONFIRM");
//      }
      break;
    case UI_SETTINGS_CHANGE_NAME:
      break;
    case UI_SETTINGS_SELECT_USER:
      break;
    case UI_SETTINGS_RESET:
      break;
    case UI_SHIP_DETAILS:
      break;
    case UI_SHIP_MISSION_SELECT:
      break;
    case UI_SHIP_DEST_SELECT:
      break;
    case UI_SHIP_CONFIRM:
      break;
    case UI_SHIP_SPLASH:
      break;
    case UI_SHIP_RENAME:
      break;
    case UI_EVENT_SHIP_VISIT:
      break;
    case UI_EVENT_PLAYER_LAUNCH:
      break;
    case UI_SHIP_VISIT_DECISION:
      break;
    case UI_SHIP_VISIT_OUTCOME:
      break;
    case UI_LAUNCH_SPLASH:
      break;
    default:
      Serial.printf("Screen not implemented: %d\n", ui);
      break;
  }
}
