#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace sf {
class  ArcShape : public Shape {
 public:
  explicit ArcShape(float radius = 0, std::size_t pointCount = 30);
  void setRadius(float radius);
  float getRadius() const;
  void setPointCount(std::size_t count);
  virtual std::size_t getPointCount() const;
  virtual Vector2f getPoint(std::size_t index) const;

 private:
  float m_radius;            ///< Radius of the circle
  std::size_t m_pointCount;  ///< Number of points composing the circle
};

}  // namespace sf
