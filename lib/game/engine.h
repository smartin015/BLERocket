#ifndef ENGINE_H
#define ENGINE_H

#include "nav.h"
#include <stdint.h>
#include "nav.capnp.h"
#include "game.capnp.h"

class Engine {
public:
  Engine() {
    page = nav::Page::MAIN;
    num_ships = 0;
  };

  void update(nav::Command cmd);

  nav::Page getPage() const;

private:
  nav::Page page;
  // game::Ship pending;
  // game::Ship ships[game::MAX_SHIPS];
  uint8_t num_ships;
};

#endif // ENGINE_H
