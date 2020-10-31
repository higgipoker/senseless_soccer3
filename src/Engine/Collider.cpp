#include "Collider.hpp"

#include "Vector.hpp"

#include<cmath>
namespace Senseless {
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
  float dist_sq = std::sqrt(((small.getCenter().x - big.getCenter().x) *
                            (small.getCenter().x - big.getCenter().x)) +
                            ((small.getCenter().y - big.getCenter().y) *
                            (small.getCenter().y - big.getCenter().y)));

  if (big.getRadius() > (dist_sq + small.getRadius())) {
    return true;
  }

  return false;
}
//
//
//
bool Collider::contains(const sf::CircleShape &circle, const sf::Vector3f &point) {
  // Compare radius of circle with distance
  // of its center from given point
  if ((point.x - circle.getCenter().x) * (point.x - circle.getCenter().x) +
          (point.y - circle.getCenter().y) * (point.y - circle.getCenter().y) <=
      circle.getRadius() * circle.getRadius())
    return true;
  else
    return false;
}
// -----------------------------------------------------------------------------
// point with triangle
//
// the Barycentric Technique using dot products to cleverly avoid roots...
// see: http://www.blackpawn.com/texts/pointinpoly/default.html
// -----------------------------------------------------------------------------
bool Collider::collides(const sf::Vector3f &point,
                        const sf::TriangleShape &triangle) {
  sf::Vector3f v0 = sf::Vector3f(triangle.getPoint(2).x, triangle.getPoint(2).y, 0) -
               sf::Vector3f(triangle.getPoint(0).x, triangle.getPoint(0).y, 0);
               
  sf::Vector3f v1 = sf::Vector3f(triangle.getPoint(1).x, triangle.getPoint(1).y,0) -
               sf::Vector3f(triangle.getPoint(0).x, triangle.getPoint(0).y, 0);
               
  sf::Vector3f v2 = sf::Vector3f(point.x, point.y, 0) -
               sf::Vector3f(triangle.getPoint(0).x, triangle.getPoint(0).y, 0);

  float dot00 = Vector::dotProduct(v0, v0);
  float dot01 = Vector::dotProduct(v0, v1);
  float dot02 = Vector::dotProduct(v0, v2);
  float dot11 = Vector::dotProduct(v1, v1);
  float dot12 = Vector::dotProduct(v1, v2);

  float inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
  float u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
  float v = (dot00 * dot12 - dot01 * dot02) * inv_denom;

  return (u >= 0) && (v >= 0) && (u + v < 1);
}

}  // namespace Senseless
