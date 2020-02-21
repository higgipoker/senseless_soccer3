#include "Entity.hpp"

#include <cassert>
namespace SoySoccer {
Entity::Entity(std::unique_ptr<Controllable> c, std::unique_ptr<Movable>& m, std::unique_ptr<Renderable>& r)
    : controllable(std::move(c)), movable(std::move(m)), renderable(std::move(r)) {
}
Controllable* Entity::GetControllable() {
    return controllable.get();
}
Movable* Entity::GetMovable() {
    return movable.get();
}
Renderable* Entity::GetRenderable() {
    return renderable.get();
}
}  // namespace SoySoccer
