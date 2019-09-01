#ifdef STATE_FS
#ifndef STATE_FS_H
#define STATE_FS_H

#include "state.h"
#include <string.h>

class StateFS : public State {
public:
  StateFS(std::string path);
  Engine load();
  bool save(const Engine& engine);
private:
  std::string path;
};

#endif // STATE_FS_H
#endif // STATE_FS
