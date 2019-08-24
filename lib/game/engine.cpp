#include "engine.h"

#include <iostream>
#include <string.h>
#include <capnp/schema.h>
// #include <capnp/dynamic.h>

template <class T> std::string enumStr(T e) {
  auto x = capnp::Schema::from<T>();
  return x.asEnum().getEnumerants()[(int)e].getProto().getName().cStr();
}

nav::Page Engine::getPage() const {
  return page;
}

void Engine::update(nav::Command cmd) {
  std::cout << "cmd: " << enumStr<nav::Command>(cmd) << std::endl;

  auto next = nextPage(this->page, cmd);
  if (next != nav::Page::NO_OP) {
    this->page = next;
    std::cout << "nav: " << enumStr<nav::Page>(this->page) << std::endl;
  }
}
