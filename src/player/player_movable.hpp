#pragma once
#include <gamelib3/compass/compass.hpp>
#include <gamelib3/physics/metrics.hpp>
#include <gamelib3/physics/movable.hpp>

namespace senseless_soccer3 {

/**
 * @brief The PlayerMovable class
 */
class PlayerMovable : public gamelib3::Movable {
 public:
  /**
   * @brief PlayerMovable
   */
  PlayerMovable();

  /**
   * @brief ~PlayerMovable
   */
  ~PlayerMovable() override;

  /**
   * @brief Init
   */
  void PopulateAnimations() override;
  void Step(float dt) override {}

  // map animations based on gamelib3::Direction
  static std::map<gamelib3::Direction, std::string> standmap;
  static std::map<gamelib3::Direction, std::string> runmap;
  static std::map<gamelib3::Direction, std::string> slidemap;
};
#include "player_statics.hpp"

}  // namespace senseless_soccer3
