#ifndef BLE_UI_H
#define BLE_UI_H

#include "engine.h"
#include "nav.capnp.h"
#include <vector>

// const char* PART_NAMES[NUM_PARTS] = {
//   "Hull",
//   "Thruster",
//   "Cargo Bay",
//   "Sensor Array",
// };

class UI {
public:
  UI() {}

  void render(const Engine& engine);
  virtual Command nextCommand() = 0;
  virtual void clear() = 0;
  virtual bool flush() = 0;

protected:
  virtual void drawText(const std::string& text, const int& size, const int& x, const int& y) = 0;
  virtual void drawShape(const std::vector<std::pair<int, int>>& points) = 0;

private:
  void drawControls(const int& cx, const int& cy, const std::string& top, const std::string& left, const std::string& bottom, const std::string& right, const std::string& center);
  void drawLaunchEntry(const Engine& engine);
  void drawTradeEntry(const Engine& engine);
  std::string getTitle(const Page& page);
};

#endif // BLE_UI_H
