#ifdef STATE_SPIFFS
#ifndef STATE_SPIFFS_H
#define STATE_SPIFFS_H

#include "state.h"

class StateSPIFFS : public State {
public:
  StateSPIFFS(std::string path);
  Engine load();
  bool save(const Engine& engine);
};

#endif // STATE_SPIFFS_H
#endif // STATE_SPIFFS
