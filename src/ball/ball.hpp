#pragma once
#include <gamelib3/engine/entity.hpp>
namespace senseless_soccer3 {

class Ball : public gamelib3::GameEntity, public gamelib3::ControllerListener {
 public:
  /**
   * @brief Player
   */
  Ball(gamelib3::Movable* m, gamelib3::Renderable* r);
  /**
   * @brief OnControllerEvent
   * @param event
   */
  void OnControllerEvent(const gamelib3::ControllerEvent& event) override;

  /**
   * @brief Update
   */
  void Update();

 protected:
  gamelib3::Sprite& sprite;
};
}  // namespace senseless_soccer3
