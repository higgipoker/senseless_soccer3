#pragma once
#include "camera.hpp"
#include "grass.hpp"
/**
 * @brief The Pitch struct
 */
struct Pitch{
    Grass grass;
};
/**
 * @brief init the pitch
 */
void init_pitch(Pitch &pitch, const std::string &grass_spritesheet, Camera &camera);
/**
 * @brief update_pitch
 * @param pitch
 */
void update_pitch(Pitch &pitch, Camera &camera);

