#ifdef UI_NATIVE
#include "ui_native.h"
#include "fonts.h"

#include <iostream>

UINative::UINative() {
  window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(EPAPER_W_PX, EPAPER_H_PX), "Rockets N'at"));
  window->setSize(sf::Vector2u(WINDOW_SCALE*EPAPER_W_PX, WINDOW_SCALE*EPAPER_H_PX));
  window->setKeyRepeatEnabled(false);
  if (!font.loadFromFile("assets/arial.ttf")) {
    std::cerr << "Could not load font" << std::endl;
  } else {
    std::cout << "Font loaded" << std::endl;
  }
  color = sf::Color::White;
}

Command UINative::nextCommand() {
  sf::Event event;
  while (window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Left:
            return nav::Command_left;
          case sf::Keyboard::Right:
            return nav::Command_right;
          case sf::Keyboard::Up:
            return nav::Command_up;
          case sf::Keyboard::Down:
            return nav::Command_down;
          case sf::Keyboard::Return:
            return nav::Command_enter;
          case sf::Keyboard::Escape:
            window->close();
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  return nav::Command_unknown;
}

void UINative::clear() {
  window->clear();
}

void UINative::partialUpdate() {
  window->display();
}

void UINative::fullUpdate() {
  window->display();
}

void UINative::loop() {
  if (window->isOpen()) {
    window->display();
  }
}

bool UINative::isOpen() {
  return window->isOpen();
}

void UINative::setFont(const FONT_T* f) {
  //TODO
}

// don't do anything here; this is for flipping the screen over for
// nametag/gameplay
void UINative::setRotation(int r) {};

// stubs
void UINative::getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h) {}
void UINative::DrawSidebarText(std::string text, bool leftside) {};
void UINative::DrawStringAt(
    std::string s,           // string to draw
    int x, int y,            // where to draw.
    int* xmax, int* ymax     // where to store bottom right coords of bounds
    ) {}

void UINative::drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation) {
  sf::Text t;
  t.setFont(font);
  t.setString(text);
  t.setPosition(x, y);
  t.setCharacterSize(size);
  t.setColor(color);
  window->draw(t);
}

void UINative::drawShape(const std::vector<std::pair<int, int>>& points) {
  sf::ConvexShape convex;
  convex.setPointCount(points.size());
  convex.setFillColor(color);
  for (int i = 0; i < points.size(); i++) {
    convex.setPoint(i, sf::Vector2f(points[i].first, points[i].second));
  }
  window->draw(convex);
}

void UINative::drawSelector(const std::vector<std::string>& items, const int& selected, const int& x, const int& y) {
  for (int i = 0; i < items.size(); i++) {
    drawText(items[i], SZ_S, x + SZ_S, y + (i*SZ_M), 0);
  }
  drawText(">", SZ_S, x, y + (selected*SZ_M), 0);
}

#endif // UI_NATIVE
