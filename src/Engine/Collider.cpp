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
  float dx = c2.getCenter().x - c1.getCenter().x;
  float dy = c2.getCenter().y - c1.getCenter().y;
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

  // distance
  int dist_sq = sqrt(((small.getCenter().x - big.getCenter().x) *
                      (small.getCenter().x - big.getCenter().x)) +
                     ((small.getCenter().y - big.getCenter().y) *
                      (small.getCenter().y - big.getCenter().y)));

  if (big.getRadius() > (dist_sq + small.getRadius())) {
    return true;
  }

  return false;
}
}  // namespace Engine
