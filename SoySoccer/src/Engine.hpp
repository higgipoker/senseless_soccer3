#pragma once
#include "Controllable.hpp"
#include "Movable.hpp"
#include "Renderable.hpp"
#include "Animation.hpp"

#include <vector>
namespace SoySoccer {
//
//
//
class Engine {
   public:
    void HandleInput();
    void Simulate(const float dt);
    void Render();
    void AddEntity(Controllable *controllable, Movable *movable, Renderable *renderable);

   protected:
    std::vector<Controllable*> controllables;
    std::vector<Movable*> movables;
    std::vector<Renderable*> renderables;
    std::vector<Animation*> animations;
};

}  // namespace SoySoccer
