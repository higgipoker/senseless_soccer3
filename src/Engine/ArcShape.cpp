#include "ArcShape.hpp"
#include "Math.hpp"

#include <cmath>

using namespace Senseless;

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
  float angle = static_cast<float>(index) * 2 * PI / m_pointCount - PI / 2;
  float x = std::cos(angle) * m_radius;
  float y = std::sin(angle) * m_radius;

  return Vector2f(m_radius + x, m_radius + y);
}

}  // namespace sf
