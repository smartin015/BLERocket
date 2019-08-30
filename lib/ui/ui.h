#ifndef BLE_UI_H
#define BLE_UI_H

#include "engine.h"
#include "nav_generated.h"
#include <vector>

#define SZ_S 10
#define SZ_M 20
#define SZ_L 30

#define BODY_X 10
#define BODY_Y 40

#define TITLE_SZ 18
#define TITLE_X 15
#define TITLE_Y 15

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

  // Individual page render functions in ./ui/pages
  void drawMain(const Engine& engine);
  void drawSettingsEntry(const Engine& engine);
  void drawTradeEntry(const Engine& engine);
  void drawFleetEntry(const Engine& engine);
  void drawLaunchEntry(const Engine& engine);
  void drawSettingsChangeName(const Engine& engine);
  void drawSettingsSelectUser(const Engine& engine);
  void drawSettingsReset(const Engine& engine);
  void drawShipDetails(const Engine& engine);
  void drawShipMissionSelect(const Engine& engine);
  void drawShipDestSelect(const Engine& engine);
  void drawShipConfirm(const Engine& engine);
  void drawShipSplash(const Engine& engine);
  void drawShipRename(const Engine& engine);
  void drawEventShipVisit(const Engine& engine);
  void drawEventPlayerLaunch(const Engine& engine);
  void drawShipVisitDecision(const Engine& engine);
  void drawShipVisitOutcome(const Engine& engine);
  void drawLaunchSplash(const Engine& engine);
};

#endif // BLE_UI_H
