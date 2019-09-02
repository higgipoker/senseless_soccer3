#pragma once
#include "data.hpp"
#include "vector.hpp"

#include <SFML/Graphics/CircleShape.hpp>

// these are used repeatedely in physics calculations
inline Vector3 friction;
inline Vector3 acceleration;
inline Vector3 dv;  // delta velocity
inline Vector3 dp;  // delta position
inline Vector3 k1;  // velocity integration step 1
inline Vector3 k2;  // velocity integration step 2

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
/**
 * @brief collides
 * @param c1
 * @param c2
 * @return
 */
bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
/**
 * @brief contains
 * @param c1
 * @param c2
 * @return
 */
bool contains(const sf::CircleShape &big, const sf::CircleShape &small);
