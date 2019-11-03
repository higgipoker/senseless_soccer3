#include "Game.hpp"
//
#include <algorithm>
#include <iostream>
//
//
//
static float MIN_KICK_LENGTH = 5;
static float MAX_KICK_LENGTH = 100;
static float FORCE_MULTIPLIER = 0.3F;
//
//
//
float fire_length_to_force(const float in_length) {
  float force = std::clamp(in_length, MIN_KICK_LENGTH, MAX_KICK_LENGTH);
  force *= FORCE_MULTIPLIER;
  std::cout << force << std::endl;
  return force;
}
