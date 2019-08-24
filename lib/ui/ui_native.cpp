#ifdef UI_NATIVE
#include "ui_native.h"

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
            return Command::LEFT;
          case sf::Keyboard::Right:
            return Command::RIGHT;
          case sf::Keyboard::Up:
            return Command::UP;
          case sf::Keyboard::Down:
            return Command::DOWN;
          case sf::Keyboard::Return:
            return Command::ENTER;
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
  return Command::UNKNOWN;
}

void UINative::clear() {
  window->clear();
}

bool UINative::flush() {
  if (!window->isOpen()) {
    return false;
  }
  window->display();
  return true;
}

void UINative::drawText(const std::string& text, const int& size, const int& x, const int& y) {
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

#endif // UI_NATIVE
