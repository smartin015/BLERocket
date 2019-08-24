#ifndef BLE_UI_H
#define BLE_UI_H

#include "game.h"
#include "actions.capnp.h"


// const char* PART_NAMES[NUM_PARTS] = {
//   "Hull",
//   "Thruster",
//   "Cargo Bay",
//   "Sensor Array",
// };

class UI {
public:
  UI() {}

  virtual Command nextCommand() = 0;

  virtual bool render(Game * game) = 0;
};

#endif // BLE_UI_H
