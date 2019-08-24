#ifndef BLE_GAME_H
#define BLE_GAME_H

#include "nav.h"
#include <stdint.h>
#include "actions.capnp.h"

class Game {
public:
  Game() {
    page = Page::MAIN;
    num_ships = 0;
  };

  void update(Command cmd);

private:
  Page page;
  ship_t ship_parts;
  ship_t ships[MAX_SHIPS];
  uint8_t num_ships;
};

#endif // BLE_GAME_H
