#ifdef STATE_SPIFFS
#ifndef STATE_SPIFFS_H
#define STATE_SPIFFS_H

#include "state.h"
#include "FS.h"
#include "SPIFFS.h"

/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED true

class StateSPIFFS : public State {
public:
  StateSPIFFS(std::string savePath, std::string metaPath);
  Engine load();
  bool save(const Engine& engine);
private:
  std::string savePath;
  std::string metaPath;
};

#endif // STATE_SPIFFS_H
#endif // STATE_SPIFFS
