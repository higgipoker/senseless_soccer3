#pragma once
#include "gamelib3/math/vector.hpp"
namespace Data {
enum class EntityType { Anonymous, Match, Player, Ball, Background, Goal };
/**
 * @brief The Entity struct
 */
struct Entity {
  EntityType type = EntityType::Anonymous;
  gamelib3::Vector3 position, velocity, force;
  float co_friction = 0.00f;
  float mass = 1;
  int sprite = 0;
};

}  // namespace Data
