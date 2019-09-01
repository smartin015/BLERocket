#ifdef STATE_FS
#ifndef STATE_FS_H
#define STATE_FS_H

#include "state.h"

class StateFS : public State {
public:
  StateFS();
  Engine load(std::string path);
  bool save(const Engine& engine);
};

#endif // STATE_FS_H
#endif // STATE_FS
