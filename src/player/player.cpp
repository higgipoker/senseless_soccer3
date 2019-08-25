#include "player.hpp"
namespace senseless_soccer3 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Player::Player(gamelib3::Movable* m, gamelib3::Renderable* r)
    : gamelib3::GameEntity(m, r), sprite(dynamic_cast<gamelib3::Sprite&>(*r)) {
  feet_collider.setRadius(10);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::OnControllerEvent(const gamelib3::ControllerEvent& event) {
  std::cout << "event" << std::endl;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::Update() {
  // input
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
    if (controller->states[static_cast<size_t>(gamelib3::InputState::Right)]) {
      physical_aspect->force.x = force;
    }
  }

  sprite.SetPosition(physical_aspect->position.x, physical_aspect->position.y);
  sprite.Perspectivize(physical_aspect->position.z, physical_aspect->width, 20);
  feet_collider.setPosition(
      physical_aspect->position.x - feet_collider.getRadius(),
      physical_aspect->position.y - feet_collider.getRadius());
  sprite.AddPrimitive(&feet_collider);
}
}  // namespace senseless_soccer3
