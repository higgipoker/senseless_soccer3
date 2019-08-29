#pragma once
#include "data.hpp"

#include "gamelib3/math/vector.hpp"

using namespace gamelib3;

inline Vector3 friction;
inline Vector3 acceleration;
inline Vector3 dv;
inline Vector3 dp;

inline Vector3 k1;
inline Vector3 k2;

/**
 * @brief integrate_euler
 * @param entity
 * @param dt
 */
void integrate_euler(Entity &entity, const float dt);
/**
 * @brief integrate_improved_euler
 * @param entity
 * @param dt
 */
void integrate_improved_euler(Entity &entity, const float dt);
