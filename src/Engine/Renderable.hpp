#pragma once
#include "Sprite.hpp"
namespace Senseless {
class Renderable {
   public:
    Renderable(std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow);
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Sprite> shadow;
};
}  // namespace Senseless
