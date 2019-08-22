#pragma once
#include <gamelib3/compass/compass.hpp>
#include <gamelib3/physics/movable.hpp>

namespace senseless_soccer3 {

/**
 * @brief The Player class
 */
class Player : public gamelib3::Movable {
 public:
  /**
   * @brief Player
   */
  Player();

  /**
   * @brief Init
   */
  void Init();

  // map animations based on direction
  static std::map<gamelib3::Direction, std::string> standmap;
  static std::map<gamelib3::Direction, std::string> runmap;
  static std::map<gamelib3::Direction, std::string> slidemap;

 private:


};

}  // namespace senseless_Soccer3
