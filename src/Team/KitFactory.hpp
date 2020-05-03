#pragma once

#include <SFML/Graphics/Color.hpp>
//
#include <vector>
namespace Senseless {
//
//
//
using KitPalette = std::vector<std::pair<sf::Color, sf::Color>>;
//
//
//
enum class KitType {
  Standard,
};
//
//
//
struct Kit {
  //
  //
  //
  Kit(KitType in_type, KitPalette in_palette) : type(in_type), palette(in_palette) {}
  KitType type;
  KitPalette palette;
};
//
//
//
class KitFactory {
 public:
  //
  //
  //
  static Kit makeDefaultRedKit();
  //
  //
  //
  static Kit makeDefaultBlueKit();
};
}  // namespace Senseless
