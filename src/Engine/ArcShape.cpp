#include "arcshape.hpp"

#include <cmath>

namespace sf {
//
//
//
ArcShape::ArcShape(float radius, std::size_t pointCount)
    : m_radius(radius), m_pointCount(pointCount) {
  update();
}
//
//
//
void ArcShape::setRadius(float radius) {
  m_radius = radius;
  update();
}
//
//
//
float ArcShape::getRadius() const { return m_radius; }
//
//
//
void ArcShape::setPointCount(std::size_t count) {
  m_pointCount = count;
  update();
}
//
//
//
std::size_t ArcShape::getPointCount() const { return (m_pointCount / 2) + 1; }
//
//
//
Vector2f ArcShape::getPoint(std::size_t index) const {
  static const float pi = 3.141592654F;

  float angle = static_cast<float>(index) * 2 * pi / m_pointCount - pi / 2;
  float x = std::cos(angle) * m_radius;
  float y = std::sin(angle) * m_radius;

  return Vector2f(m_radius + x, m_radius + y);
}

}  // namespace sf
