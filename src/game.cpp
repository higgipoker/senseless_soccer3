#include "game.hpp"
//
//
//
void init(Game &game) {
  init_window(game.window, game.window_title, game.window_rect.width,
              game.window_rect.height, sf::Style::Default);
}
