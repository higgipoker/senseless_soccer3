#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace sf {
/**
 * @brief The TriangleShape class
 */
class TriangleShape : public Shape {
 public:
  /**
   * @brief TriangleShape
   * @param radius
   * @param pointCount
   */
  explicit TriangleShape();
  /**
   * @brief setPoints
   * @param p1
   * @param p2
   * @param p3
   */
  void setPoints(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
  /**
   * @brief reset
   */
  void reset();
  /**
   * @brief getPointCount
   * @return
   */
  std::size_t getPointCount() const override { return 3; }
  /**
   * @brief getPoint
   * @param index
   * @return
   */
  Vector2f getPoint(std::size_t index) const override;

 private:
  Vector2f points[3];
};

}  // namespace sf
