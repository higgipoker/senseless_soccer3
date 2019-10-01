#include "Collider.hpp"

#include "Vector.hpp"
namespace Engine {
//
//
//
bool Collider::collides(const sf::CircleShape &c1, const sf::CircleShape &c2) {
  // One of the circles has no size
  if (Math::equal(c1.getRadius(), 0) || Math::equal(c2.getRadius(), 0)) {
    return false;
  }

  // compare the distance to combined radii
  float dx = c2.getPosition().x - c1.getPosition().x;
  float dy = c2.getPosition().y - c1.getPosition().y;
  float radii = c1.getRadius() + c2.getRadius();

  if ((dx * dx) + (dy * dy) < radii * radii) {
    return true;
  }
  return false;
}
//
//
//
bool Collider::contains(const sf::CircleShape &big,
                        const sf::CircleShape &small) {
  // get the center points of circles
  sf::Vector2 center_big_circle(big.getPosition().x + big.getRadius(),
                                big.getPosition().y + big.getRadius());
  sf::Vector2 center_small_circle(small.getPosition().x + small.getRadius(),
                                  small.getPosition().y + small.getRadius());

  // distance
  int dist_sq = sqrt(((center_small_circle.x - center_big_circle.x) *
                      (center_small_circle.x - center_big_circle.x)) +
                     ((center_small_circle.y - center_big_circle.y) *
                      (center_small_circle.y - center_big_circle.y)));

  if (big.getRadius() > (dist_sq + small.getRadius())) {
    return true;
  }

  return false;
}
}  // namespace Engine
