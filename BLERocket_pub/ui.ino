#include "ui.h"

// Un/Comment this to switch between screen and console rendering
#define CONSOLE_RENDER
#define CONSOLE_RENDER_PD_MILLIS 500

ui_t current_ui = UI_MAIN;

// Target vs Item selector
bool giveTarget;
uint8_t partSel;
uint8_t destSel;

//uint8_t uiNavigate(ui_t ui, cmd_t cmd) {
//  return NAV_STATE_TRANSITION[ui][cmd];
// }

//void handleStatusScreen(cmd_t cmd) {
//  switch (cmd) {
//    case CMD_LEFT:
//      currentScreen = SCREEN_OFF;
//      break;
//    case CMD_DOWN:
//      currentScreen = SCREEN_MAKE;
//      break;
//    case CMD_RIGHT:
//      giveTarget = false;
//      partSel = 0;
//      for (int i = 0; i < NUM_PARTS; i++) {
//        if (parts[i] != 0)  {
//          partSel = i;
//          break;
//        }
//      }
//      destSel = 0;
//      currentScreen = SCREEN_GIVE;
//      break;
//    case CMD_UP:
//      currentScreen = SCREEN_LAUNCH;
//      break;
//    default:
//      break;
//  }
//}

//void handleMakeScreen(cmd_t cmd) {
//  switch (cmd) {
//    case CMD_LEFT:
//    case CMD_DOWN:
//    case CMD_RIGHT:
//    case CMD_UP:
//    case CMD_ENTER:
//      parts[USER_PART] = 5;
//      Serial.printf("Made part: %s quality %d\n", PART_NAMES[USER_PART], parts[USER_PART]);
//    default:
//      currentScreen = SCREEN_STATUS;
//      break;
//  }
//}

//void handleGiveScreen(cmd_t cmd) {
//  int dir;
//  uint8_t next;
//  switch (cmd) {
//    case CMD_LEFT:
//      if (giveTarget == false) {
//        currentScreen = SCREEN_STATUS;
//      } else {
//        giveTarget != giveTarget;
//      }
//      break;
//    case CMD_RIGHT:
//      giveTarget = !giveTarget;
//      break;
//    case CMD_UP:
//    case CMD_DOWN:
//      dir = 2*(int(cmd == CMD_DOWN))-1;
//      if (!giveTarget) {
//        next = partSel;
//        for (int i = 1; i < NUM_PARTS; i++) {
//          next = (partSel+(i*dir)) % NUM_PARTS;
//          if (parts[next] > 0) {
//            partSel = next;
//            break;
//          }
//        }
//      } else {
//        next = destSel;
//        for (int i = 1; i < num_dests; i++) {
//          next = (destSel+(i*dir)) % num_dests;
//          if (dests[next] > 0) {
//            destSel = next;
//            break;
//          }
//        }
//      }
//      break;
//    case CMD_ENTER:
//      // setPartActionMessage()
//      Serial.println("TODO give completion");
//      break;
//    default:
//      currentScreen = SCREEN_STATUS;
//      break;
//  }
// }

//void handleLaunchScreen(cmd_t cmd) {
//  switch (cmd) {
//    case CMD_LEFT:
//      currentScreen = SCREEN_STATUS;
//      break;
//    case CMD_ENTER:
//      // Can only launch with all parts
//      for (int i = 0; i < NUM_PARTS; i++) {
//        if (parts[i] == 0) {
//          return;
//        }
//      }
//      Serial.println("Launch launch launch!");
//      currentScreen = SCREEN_STATUS;
//      break;
//    case CMD_DOWN:
//    case CMD_RIGHT:
//    case CMD_UP:
//    default:
//      break;
//  }
//}

//void handleCmd(cmd_t cmd) {
//  switch (currentScreen) {
//    case SCREEN_OFF: // Wake up screen on any input
//      currentScreen = SCREEN_STATUS;
//      break;
//    case SCREEN_STATUS:
//      handleStatusScreen(cmd);
//      break;
//    case SCREEN_MAKE:
//      handleMakeScreen(cmd);
//      break;
//    case SCREEN_GIVE:
//      handleGiveScreen(cmd);
//      break;
//    case SCREEN_LAUNCH:
//      handleLaunchScreen(cmd);
//      break;
//    default:
//      Serial.printf("handleCmd: Unknown current screen %d\n", currentScreen);
//      break;
//  }
//}

void handleInput(char c) {
  switch(c) {
    case 'w':
      //handleCmd(CMD_UP);
      break;
    case 'a':
      //handleCmd(CMD_LEFT);
      break;
    case 's':
      //handleCmd(CMD_DOWN);
      break;
    case 'd':
      //handleCmd(CMD_RIGHT);
      break;
    case 'e':
      //handleCmd(CMD_ENTER);
      break;
    default:
      break;
  }
}

uint64_t lastRender = 0;
void maybeRender(ui_t ui) {
  if (lastRender + CONSOLE_RENDER_PD_MILLIS > millis()) {
    return;
  }
  lastRender = millis();
#ifdef CONSOLE_RENDER
  consoleRender(ui);
#else
  lcdRender();
#endif
}
