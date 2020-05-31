#include "Renderable.hpp"

namespace Senseless {
//
//
//
Renderable::Renderable(std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow)
    : sprite(std::move(in_sprite)), shadow(std::move(in_shadow)){

}
}
