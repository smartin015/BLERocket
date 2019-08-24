#include "game.h"

#include <iostream>
#include <string.h>
#include <capnp/schema.h>
#include <capnp/dynamic.h>

template <class T> std::string enumStr(T e) {
  auto x = capnp::Schema::from<T>();
  return x.asEnum().getEnumerants()[(int)e].getProto().getName().cStr();
}

void Game::update(Command cmd) {

  std::cout << "Received command: " << enumStr<Command>(cmd) << std::endl;

  auto next = nextPage(this->page, cmd);
  if (next != Page::NO_OP) {
    this->page = next;
    std::cout << "Switched to page " << enumStr<Page>(this->page) << std::endl;
  }
}
