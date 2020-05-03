#pragma once
#include "Sprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
namespace Senseless {
//
//
//
class Widget : public Sprite {
 public:
  //
  //
  //
  Widget() = default;
  //
  //
  //
  virtual ~Widget() = default;
  //
  //
  //
  virtual void update() = 0;
  //
  //
  //
  void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

}  // namespace Senseless
