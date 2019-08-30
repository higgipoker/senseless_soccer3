#pragma once
#include "gamelib3/math/vector.hpp"
enum class EntityType {
  Anonymous,
  Camera,
  Match,
  Player,
  Ball,
  Background,
  Goal
};
/**
 * @brief The Entity struct
 */
struct Entity {
  int id = -1;
  EntityType type = EntityType::Anonymous;
  gamelib3::Vector3 position, velocity, force;
  float terminal_velocity = 1;
  float co_friction = 0.01f;
  float mass = 1;
  int sprite = 0;
};
/**
 * @brief apply_force
 * @param entity
 * @param force
 */
void apply_force(Entity& entity, gamelib3::Vector3 force);
