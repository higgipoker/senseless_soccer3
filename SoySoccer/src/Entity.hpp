#pragma once
#include "Controllable.hpp"
#include "Movable.hpp"
#include "Renderable.hpp"

#include <memory>

namespace SoySoccer {
//
//
//
class Entity {
    Entity(std::unique_ptr<Controllable> c, std::unique_ptr<Movable>& m, std::unique_ptr<Renderable>& r);
    Controllable* GetControllable();
    Movable* GetMovable();
    Renderable* GetRenderable();

   public:
   protected:
    std::unique_ptr<Controllable> controllable;
    std::unique_ptr<Movable> movable;
    std::unique_ptr<Renderable> renderable;
};
}  // namespace SoySoccer
