#ifndef STATE_H
#define STATE_H

#include "engine.h"

class State {
public:
  virtual Engine load(std::string path) = 0;
  virtual bool save(const Engine& engine) = 0;
};

#endif // STATE_H
