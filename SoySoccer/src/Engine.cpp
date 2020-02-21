#include "Engine.hpp"
namespace SoySoccer {
//
//
//
void Engine::AddEntity(Controllable *controllable, Movable *movable, Renderable *renderable) {
    controllables.push_back(controllable);
    movables.push_back(movable);
    renderables.push_back(renderable);
}
//
//
//
void Engine::HandleInput() {
    for (auto &controllable : controllables) {
        controllable->HandleInput();
    }
}
//
//
//
void Engine::Simulate(const float dt) {
    for (auto &movable : movables) {
        movable->Simulate(dt);
    }
}
//
//
//
void Engine::Render() {
    for(auto &animation : animations){
        animation->Update();
    }
    for (auto &renderable : renderables) {
        renderable->Render();
    }
}
}  // namespace SoySoccer
