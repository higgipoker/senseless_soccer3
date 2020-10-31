#pragma once
#include "Engine/TriangleShape.hpp"
#include "Engine/Vector.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Senseless {
//
//
//
class Collider {
 public:
  static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
  static bool contains(const sf::CircleShape &big, const sf::CircleShape &small);
  static bool contains(const sf::CircleShape &circle, const sf::Vector3f &point);
  static bool collides(const sf::Vector3f &point, const sf::TriangleShape &triangle);
  template <class R, class P>
  static bool contains(R in_rect, P in_point) {
    if (in_point.x > in_rect.left && in_point.x < in_rect.left + in_rect.width &&
        in_point.y > in_rect.top && in_point.y < in_rect.top + in_rect.height) {
      return true;
    }
    return false;
  }
  static bool contains(sf::RectangleShape in_rect, sf::Vector3f in_point) {
      if (in_point.x > in_rect.getPosition().x && in_point.x < in_rect.getPosition().x+ in_rect.getSize().x &&
          in_point.y > in_rect.getPosition().y && in_point.y < in_rect.getPosition().y + in_rect.getSize().y) {
          return true;
      }
      return false;
  }
};
}  // namespace Senseless
