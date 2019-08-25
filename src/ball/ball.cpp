#include "ball.hpp"

namespace senseless_soccer3 {
Ball::Ball(gamelib3::Movable* m, gamelib3::Renderable* r)
    : gamelib3::GameEntity(m, r), sprite(dynamic_cast<gamelib3::Sprite&>(*r)) {}

void Ball::Update() {
  sprite.SetPosition(physical_aspect->position.x, physical_aspect->position.y);
  sprite.Perspectivize(physical_aspect->position.z, physical_aspect->width, 20);
}

void Ball::OnControllerEvent(const gamelib3::ControllerEvent& event) {
  if (event.id == gamelib3::ControllerEventID::Fire) {
    static const int force = 10;
    if (controller) {
      if (controller->states[static_cast<size_t>(gamelib3::InputState::Down)]) {
        physical_aspect->force.y = force;
      }
      if (controller->states[static_cast<size_t>(gamelib3::InputState::Up)]) {
        physical_aspect->force.y = -force;
      }
      if (controller->states[static_cast<size_t>(gamelib3::InputState::Left)]) {
        physical_aspect->force.x = -force;
      }
      if (controller
              ->states[static_cast<size_t>(gamelib3::InputState::Right)]) {
        physical_aspect->force.x = force;
      }
    }
  }
}

}  // namespace senseless_soccer3
