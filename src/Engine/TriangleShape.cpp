#include "TriangleShape.hpp"
#include "Math.hpp"

#include <cmath>

using namespace Engine;

namespace sf {
//
//
//
TriangleShape::TriangleShape() { update(); }
//
//
//
void TriangleShape::setPoints(sf::Vector2f p1, sf::Vector2f p2,
                              sf::Vector2f p3) {
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;
  update();
}
//
//
//
void TriangleShape::reset(){
  points[0] = points[1] = points[2] = {0,0};
  update();
}
//
//
//
Vector2f TriangleShape::getPoint(std::size_t index) const {
  return points[index];
}

}  // namespace sf
