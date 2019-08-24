#ifdef UI_NATIVE
#ifndef UI_NATIVE_H
#define UI_NATIVE_H

#include "actions.capnp.h"
#include "ui.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <memory>

#define EPAPER_W_PX  250
#define EPAPER_H_PX  122

class UINative : UI {
public:
  UINative();
  Command nextCommand();
  bool render(Game * game);
private:
  std::unique_ptr<sf::RenderWindow> window;
};

#endif // UI_NATIVE_H
#endif // UI_NATIVE
