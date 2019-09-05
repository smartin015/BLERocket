#ifdef STATE_DUMMY
#ifndef STATE_DUMMY_H
#define STATE_DUMMY_H

#include <string.h>
#include "state.h"

class StateDummy : public State {
public:
  StateDummy();
  Engine load();
  bool save(const Engine* engine);
};

#endif // STATE_DUMMY_H
#endif // STATE_DUMMY
