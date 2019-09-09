#ifdef UI_NATIVE
#ifndef UI_NATIVE_H
#define UI_NATIVE_H

#include "nav_generated.h"
#include "ui.h"
#include "engine.h"
#include <SFML/Graphics.hpp>
#include <memory>

#define WINDOW_SCALE 2
#define EPAPER_W_PX  250
#define EPAPER_H_PX  122

#include "fonts.h"

class UINative : public UI {
public:
  UINative();
  Command nextCommand();
  void clear();
  void drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation);
  void drawShape(const std::vector<std::pair<int, int>>& points);
  void partialUpdate();
  void fullUpdate();
  void loop();
  bool isOpen();
  void setFont(const FONT_T* f);
  void getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h);
  void setRotation(int r);
  void DrawSidebarText(std::string text, bool leftside);
  void alertThePlayer();
private:
  void DrawStringAt(
      std::string s,           // string to draw
      int x, int y,            // where to draw.
      int* xmax, int* ymax     // where to store bottom right coords of bounds
      );
  std::unique_ptr<sf::RenderWindow> window;
  std::vector<sf::Font> fonts;
  const FONT_T* font;
};

#endif // UI_NATIVE_H
#endif // UI_NATIVE
