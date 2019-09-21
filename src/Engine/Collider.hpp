#pragma once
#include <SFML/Graphics/CircleShape.hpp>
namespace Engine{
/**
 * @brief The Collider class
 */
class Collider {
 public:
  /**
   * @brief circle v circle
   * @return
   */
  static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
  /**
   * @brief contains
   * @param big
   * @param small
   * @return
   */
  static bool contains(const sf::CircleShape &big, const sf::CircleShape &small);
};
}
