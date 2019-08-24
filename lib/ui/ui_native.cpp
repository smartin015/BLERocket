#include "ui_native.h"

UINative::UINative() {
  window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(EPAPER_W_PX, EPAPER_H_PX), "Rockets N'at"));
  window->setKeyRepeatEnabled(false);
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

bool UINative::render(Game * game) {
  if (!window->isOpen()) {
    return false;
  }

  window->clear();

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  window->draw(shape);

  window->display();

  return true;
}
