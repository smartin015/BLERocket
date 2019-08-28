#ifndef ENGINE_H
#define ENGINE_H

#include "nav.h"
#include <stdint.h>
#include <vector>
#include "nav.capnp.h"
#include "game.capnp.h"
#include "message.capnp.h"
#include <capnp/message.h>

// Define ShipType as POCS
typedef struct {
  std::string name;
  std::map<game::ShipPartType, uint8_t> parts;
  std::vector<uint8_t> creators;
  uint8_t owner;
} ShipType;

class Engine {
public:
  Engine();

  void handleInput(const nav::Command& cmd);
  void handleMessage(const message::Message& msg);

  nav::Page getPage() const;
  const std::map<game::ShipPartType, uint8_t> getParts() const;

  bool suppressNav(const nav::Command& cmd) const;

private:
  nav::Page page;
  // game::ShipPart
  std::map<game::ShipPartType, uint8_t> parts;
  // game::Ship
  std::vector<ShipType> ships;
};

#endif // ENGINE_H
