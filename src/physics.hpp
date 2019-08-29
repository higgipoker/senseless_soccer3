#pragma once
#include "data.hpp"

#include "gamelib3/math/vector.hpp"

using namespace gamelib3;

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
