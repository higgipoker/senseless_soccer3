#pragma once
#include "Sprite.hpp"
namespace Senseless {
class Renderable {
   public:
    Renderable(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow);
    UniquePtr<Sprite> sprite;
    UniquePtr<Sprite> shadow;
};
}  // namespace Senseless
