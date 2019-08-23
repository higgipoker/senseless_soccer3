#pragma once
#include <gamelib3/engine/entity.hpp>

#include <gamelib3/input/controller.hpp>

namespace senseless_soccer3 {

/**
 * @brief The Player class
 */
class Player : public gamelib3::GameEntity,
               public gamelib3::ControllerListener {
 public:
  /**
   * @brief Player
   */
  Player(gamelib3::Movable* m, gamelib3::Renderable* r);

  /**
   * @brief OnControllerEvent
   * @param event
   */
  void OnControllerEvent(const gamelib3::ControllerEvent& event);

  /**
   * @brief Update
   */
  void Update();

  gamelib3::Controller* controller = nullptr;
};

}  // namespace senseless_soccer3
