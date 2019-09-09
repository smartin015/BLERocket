#ifdef UI_NATIVE
#include "ui_native.h"
#include "fonts.h"

#include <iostream>

UINative::UINative() {
  window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(EPAPER_W_PX, EPAPER_H_PX), "Rockets N'at"));
  window->setSize(sf::Vector2u(WINDOW_SCALE*EPAPER_W_PX, WINDOW_SCALE*EPAPER_H_PX));
  window->setKeyRepeatEnabled(false);

  fonts.resize(NUM_FONT_PATHS);
  for (int i = 0; i < NUM_FONT_PATHS; i++) {
    if (!fonts[i].loadFromFile(font_paths[i])) {
      std::cerr << "Could not load font" << std::endl;
    } else {
      const auto& info = fonts[i].getInfo();
      std::cout << "Font loaded: " << info.family << std::endl;
    }
  }
  setFont(KNOWN_FONTS_DISPLAY[0]);
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
  window->clear(sf::Color::White);
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
  font = f;
}

// don't do anything here; this is for flipping the screen over for
// nametag/gameplay
void UINative::setRotation(int r) {};

// stubs
void UINative::getTextBounds(std::string s, int* xmin, int* ymin, int* w, int* h) {}
void UINative::DrawSidebarText(std::string text, bool leftside) {
  sf::RectangleShape r(sf::Vector2f(SIDEBAR_WIDTH, EPAPER_SHORT_DIMENSION));
  r.setFillColor(sf::Color::Black);
  window->draw(r);

  sf::Text t;
  t.setFont(fonts[font->idx]);
  t.setString(text);
  t.setPosition(0, 0);
  t.setRotation(90);
  t.setCharacterSize(font->size);
  t.setColor(sf::Color::White);
  window->draw(t);
};
void UINative::DrawStringAt(
    std::string s,           // string to draw
    int x, int y,            // where to draw.
    int* xmax, int* ymax     // where to store bottom right coords of bounds
    ) {
  sf::Text t;
  t.setFont(fonts[font->idx]);
  t.setString(s);
  t.setPosition(x, y);
  t.setCharacterSize(font->size);
  t.setColor(sf::Color::Black);
  window->draw(t);
  const auto rect = t.getGlobalBounds();
  if (xmax != NULL) {
    *xmax = rect.left + rect.width;
  }
  if (ymax != NULL) {
    *ymax = rect.top + rect.height;
  }
}

void UINative::drawText(const std::string& text, const int& size, const int& x, const int& y, int rotation) {
  sf::Text t;
  t.setFont(fonts[font->idx]);
  t.setString(text);
  t.setPosition(x, y);
  t.setRotation(rotation);
  t.setCharacterSize(font->size);
  t.setColor(sf::Color::Black);
  window->draw(t);
}

void UINative::drawShape(const std::vector<std::pair<int, int>>& points) {
  sf::ConvexShape convex;
  convex.setPointCount(points.size());
  convex.setFillColor(sf::Color::Black);
  for (int i = 0; i < points.size(); i++) {
    convex.setPoint(i, sf::Vector2f(points[i].first, points[i].second));
  }
  window->draw(convex);
}

#endif // UI_NATIVE
