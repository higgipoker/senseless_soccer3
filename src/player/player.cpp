#include "player.hpp"
namespace senseless_soccer3 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Player::Player(gamelib3::Movable* m, gamelib3::Renderable* r)
    : gamelib3::GameEntity(m, r), sprite(static_cast<gamelib3::Sprite&>(*r)) {
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
  if (controller) {
    if (controller->states[static_cast<size_t>(gamelib3::InputState::Down)]) {
      physical_aspect->position.y++;
    }
    if (controller->states[static_cast<size_t>(gamelib3::InputState::Up)]) {
      physical_aspect->position.y--;
    }
    if (controller->states[static_cast<size_t>(gamelib3::InputState::Left)]) {
      physical_aspect->position.x--;
    }
    if (controller->states[static_cast<size_t>(gamelib3::InputState::Right)]) {
      physical_aspect->position.x++;
    }
  }

  sprite.SetPosition(physical_aspect->position.x, physical_aspect->position.y);

  sprite.Perspectivize(physical_aspect->position.z, physical_aspect->width, 20);

  feet_collider.setPosition(physical_aspect->position.x,
                            physical_aspect->position.y);
  sprite.AddPrimitive(&feet_collider);
}
}  // namespace senseless_soccer3
