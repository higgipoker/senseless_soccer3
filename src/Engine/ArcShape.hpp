#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace sf {
  /**
 * @brief The ArcShape class
 */
class  ArcShape : public Shape {
 public:
  /**
   * @brief ArcShape
   * @param radius
   * @param pointCount
   */
  explicit ArcShape(float radius = 0, std::size_t pointCount = 30);
  /**
   * @brief setRadius
   * @param radius
   */
  void setRadius(float radius) ;
  /**
   * @brief getRadius
   * @return
   */
  float getRadius() const;
  /**
   * @brief setPointCount
   * @param count
   */
  void setPointCount(std::size_t count);
  /**
   * @brief getPointCount
   * @return
   */
   std::size_t getPointCount() const override;
  /**
   * @brief getPoint
   * @param index
   * @return
   */
   Vector2f getPoint(std::size_t index) const override;

 private:
  float m_radius;            ///< Radius of the circle
  std::size_t m_pointCount;  ///< Number of points composing the circle
};

}  // namespace sf
