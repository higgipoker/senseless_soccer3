#pragma once
#include "Vector.hpp"
//
#include <SFML/Graphics/Rect.hpp>
//
namespace Senseless {
class CoordinateSystem {
 public:
  static void init(const sf::FloatRect in_dimensions);
  static inline Vector3 toScreenspace(const Vector3 &in_vector);
  static inline Vector3 fromScreenspace(const Vector3 &in_vector);

 private:
  sf::FloatRect dimensions;
};
}  // namespace Senseless
