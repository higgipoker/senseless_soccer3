#pragma once
#include "gamelib3/math/vector.hpp"
enum class EntityType {
  Anonymous,
  Camera,
  Match,
  Player,
  Ball,
  Background,
  Goal,
  Shadow
};
/**
 * @brief The PhysicalEnvironemnt struct
 */
struct PhysicalEnvironemnt {};
/**
 * @brief The Entity struct
 */
struct Entity {
  int id = -1;
  int sprite = -1;
  float speed = 1.0f;
  EntityType type = EntityType::Anonymous;
  gamelib3::Vector3 position, velocity, force;
  float terminal_velocity = 1;
  float co_friction = 0.01f;
  float co_bounciness = 0.0f;
  float mass = 10;
};
/**
 * @brief apply_force
 * @param entity
 * @param force
 */
void apply_force(Entity& entity, gamelib3::Vector3 force);
