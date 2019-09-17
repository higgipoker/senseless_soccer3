#pragma once

#include <SFML/Graphics/Drawable.hpp>

/**
 * @brief The Drawable class
 */
class Drawable : public sf::Drawable {
 public:
  int z = 0;
};
