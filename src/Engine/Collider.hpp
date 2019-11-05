#pragma once
#include "Engine/Vector.hpp"
#include "Engine/TriangleShape.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
namespace Engine {
//
//
//
class Collider {
 public:
  //
  //
  //
  static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
  //
  //
  //
  static bool contains(const sf::CircleShape &big,
                       const sf::CircleShape &small);
  //
  //
  //
  static bool contains(const sf::CircleShape &circle, const Vector3 &point);
  //
  //
  //
  static bool collides(const Engine::Vector3 &point, const sf::TriangleShape &triangle);
};
}  // namespace Engine
