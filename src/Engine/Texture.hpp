#pragma once
#include <SFML/Graphics/Texture.hpp>

#include <map>
namespace Engine {
//
//
//
class Texture : public sf::Texture {
 public:
  void swapColors(const std::vector<std::pair<sf::Color, sf::Color>> &in_palette);
};
}  // namespace Engine
