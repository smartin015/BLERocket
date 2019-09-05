#ifdef STATE_DUMMY

#include "state_dummy.h"

StateDummy::StateDummy() {}

Engine StateDummy::load() {
  return Engine(NULL, NULL);
}

bool StateDummy::save(const Engine* engine) {return true;}

#endif
