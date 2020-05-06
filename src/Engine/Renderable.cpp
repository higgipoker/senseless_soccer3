#include "Renderable.hpp"

namespace Senseless {
Renderable::Renderable(UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow)
    : sprite(std::move(in_sprite)), shadow(std::move(in_shadow)){

}
}
