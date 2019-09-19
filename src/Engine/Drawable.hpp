#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Engine {
/**
 * @brief The Drawable class
 */
class Drawable : public sf::Drawable {
 public:
  /// for sorting
  int z = 0;
};

}  // namespace Engine
