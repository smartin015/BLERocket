#include "schema.h"

// Un/Comment this to switch between screen and console rendering
#define CONSOLE_RENDER
#define CONSOLE_RENDER_PD_MILLIS 500

screen_t currentScreen = SCREEN_OFF;

// Target vs Item selector
bool giveTarget;
uint8_t partSel;
uint8_t destSel;

void handleStatusScreen(cmd_t cmd) {
  switch (cmd) {
    case CMD_LEFT:
      currentScreen = SCREEN_OFF;
      break;
    case CMD_DOWN:
      currentScreen = SCREEN_MAKE;
      break;
    case CMD_RIGHT:
      giveTarget = false;
      partSel = 0;
      for (int i = 0; i < NUM_PARTS; i++) {
        if (parts[i] != 0)  {
          partSel = i;
          break;
        }
      }
      destSel = 0;
      currentScreen = SCREEN_GIVE;
      break;
    case CMD_UP:
      currentScreen = SCREEN_LAUNCH;
      break;
    default:
      break;
  }
}

void handleMakeScreen(cmd_t cmd) {
  switch (cmd) {
    case CMD_LEFT:
    case CMD_DOWN:
    case CMD_RIGHT:
    case CMD_UP:
    case CMD_ENTER:
      parts[USER_PART] = 5;
      Serial.printf("Made part: %s quality %d\n", PART_NAMES[USER_PART], parts[USER_PART]);
    default:
      currentScreen = SCREEN_STATUS;
      break;
  }
}

void handleGiveScreen(cmd_t cmd) {
  int dir;
  uint8_t next;
  switch (cmd) {
    case CMD_LEFT:
      if (giveTarget == false) {
        currentScreen = SCREEN_STATUS;
      } else {
        giveTarget != giveTarget;
      }
      break;
    case CMD_RIGHT:
      giveTarget = !giveTarget;
      break;
    case CMD_UP:
    case CMD_DOWN:
      dir = 2*(int(cmd == CMD_DOWN))-1;
      if (!giveTarget) {
        next = partSel;
        for (int i = 1; i < NUM_PARTS; i++) {
          next = (partSel+(i*dir)) % NUM_PARTS;
          if (parts[next] > 0) {
            partSel = next;
            break; 
          }
        }
      } else {
        next = destSel;
        for (int i = 1; i < num_dests; i++) {
          next = (destSel+(i*dir)) % num_dests;
          if (dests[next] > 0) {
            destSel = next;
            break; 
          }
        }
      }
      break;
    case CMD_ENTER:
      // setPartActionMessage()
      Serial.println("TODO give completion");
      break;
    default:
      currentScreen = SCREEN_STATUS;
      break;
  }
}

void handleLaunchScreen(cmd_t cmd) {
  switch (cmd) {
    case CMD_LEFT:
      currentScreen = SCREEN_STATUS;
      break;
    case CMD_ENTER:
      // Can only launch with all parts
      for (int i = 0; i < NUM_PARTS; i++) {
        if (parts[i] == 0) {
          return;
        }
      }
      Serial.println("Launch launch launch!");
      currentScreen = SCREEN_STATUS;
      break;
    case CMD_DOWN:
    case CMD_RIGHT:
    case CMD_UP:
    default:
      break;
  }
}

void handleCmd(cmd_t cmd) {
  switch (currentScreen) {
    case SCREEN_OFF: // Wake up screen on any input
      currentScreen = SCREEN_STATUS;
      break;
    case SCREEN_STATUS:
      handleStatusScreen(cmd);
      break;
    case SCREEN_MAKE:
      handleMakeScreen(cmd);
      break;
    case SCREEN_GIVE:
      handleGiveScreen(cmd);
      break;
    case SCREEN_LAUNCH:
      handleLaunchScreen(cmd);
      break;
    default:
      Serial.printf("handleCmd: Unknown current screen %d\n", currentScreen);
      break;
  }
}

void handleInput() {
  while (Serial.available()) {
    char c = Serial.read();
    switch(c) {
      case 'w':
        handleCmd(CMD_UP);
        break;
      case 'a':
        handleCmd(CMD_LEFT);
        break;
      case 's':
        handleCmd(CMD_DOWN);
        break;
      case 'd':
        handleCmd(CMD_RIGHT);
        break;
      case 'e':
        handleCmd(CMD_ENTER);
        break;
      default:
        break;
    }
  }
}

void consoleRender() {
  if (currentScreen == SCREEN_OFF) {
    return;
  }

  String needed;
  Serial.println("---");
  switch (currentScreen) {
    case SCREEN_STATUS:
      Serial.println("Status");
      Serial.println("Part (quality):");
      for (int i = 0; i < NUM_PARTS; i++) {
        if (parts[i] == 0) {
          continue;
        }
        Serial.printf("%s (%d)\n", PART_NAMES[i], parts[i]);
      }

      if (num_rockets > 0) {
        Serial.println("Rockets:");
        for (int i = 0; i < num_rockets; i++) {
            Serial.printf("%d - cargo %d speed %d c %d d %d\n", 
              i,
              rockets[i].cargo, 
              rockets[i].spd,
              rockets[i].c, 
              rockets[i].d);
        }
      }
      Serial.println("Commands: < CANCEL | v MAKE | > GIVE | ^ LAUNCH");
      break;
    case SCREEN_MAKE:
      Serial.println("Make");
      Serial.println(PART_NAMES[USER_PART]);
      Serial.println("Commands: < BACK | X MAKE");
      break;
    case SCREEN_GIVE:
      Serial.println("Give");
      if (!giveTarget) {
        Serial.println("Select part:");
        for (int i = 0; i < NUM_PARTS; i++) {
          if (parts[i] == 0) {
            continue;
          }
          if (partSel == i) {
            Serial.print("> ");
          } else {
            Serial.print("  ");
          }
          Serial.printf("%s (quality %d)\n", PART_NAMES[i], parts[i]);
        }
      } else {
        Serial.println("Select target:");
        for (int i = 0; i < num_dests; i++) {
          if (destSel == i) {
            Serial.print("> ");
          } else {
            Serial.print("  ");
          }
          Serial.printf("%d\n", dests[i]);
        }
      }
      Serial.println("Commands: << BACK | >< DEST/PRT | ^v SEL | X GIVE");
      break;
    case SCREEN_LAUNCH:
      Serial.println("Launch");
      for (int i = 0; i < NUM_PARTS; i++) {
        if (parts[i] == 0) {
          needed += PART_NAMES[i];
          needed += " ";
        }
      }
      if (needed.length() > 0) {
        Serial.printf("Still need: %s\n", needed);
        Serial.println("Commands: << BACK");
      } else {
        Serial.println("Launch new rocket with current parts?");
        Serial.println("Commands: << BACK | X CONFIRM");
      }
      break;
    default:
      Serial.printf("Screen not implemented: %d\n", currentScreen);
      break;
  }
}

uint64_t lastRender = 0;
void maybeRender() {
  if (lastRender + CONSOLE_RENDER_PD_MILLIS > millis()) {
    return;
  }
  lastRender = millis();
#ifdef CONSOLE_RENDER
  consoleRender();
#else
  lcdRender();
#endif
}
