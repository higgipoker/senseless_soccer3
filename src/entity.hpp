#pragma once
#include "compass.hpp"
#include "vector.hpp"

// unused entites have id -1
static const int NO_ENTITY = -1;

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
 * @brief The Entity struct
 */
struct Entity {
  int id = -1;
  int sprite = -1;
  float speed = 1.0f;
  EntityType type = EntityType::Anonymous;
  Vector3 position, velocity, force;
  float terminal_velocity = 1;
  float co_friction = 0.01f;
  float co_bounciness = 0.0f;
  float co_air_resistance = 0.0f;
  float mass = 1;
};
/**
 * @brief get_entity
 * @param id
 * @return
 */
Entity &get_entity(int id);
/**
 * @brief apply_force
 * @param entity
 * @param force
 */
void apply_force(Entity &entity, Vector3 force);
/**
 * @brief direction_to
 * @param from
 * @param to
 * @return
 */
Direction direction_to(const Entity &from, const Entity &to);
/**
 * @brief direction_to
 * @param from
 * @param to
 * @return
 */
Direction direction_to(const Vector3 &from, const Vector3 &to);
