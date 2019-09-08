#pragma once
#include "camera.hpp"
#include "globals.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

// types of grass
const std::array<std::string, 6> grasses{
    "grass_checked",    "grass_dry",   "grass_hard",
    "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

// grass to use
inline std::string grass_tile{Globals::GFX_FOLDER + grasses.at(0) + ".png"};

/**
 * @brief The PitchDimensions struct
 */
struct PitchDimensions {
  // pitch lines
  sf::RectangleShape bounds;
  sf::FloatRect north_6;
  sf::FloatRect north_18;
  sf::FloatRect south_6;
  sf::FloatRect south_18;
  int center_circle_radius = 0;

  // points of interest
  Vector3 center;
};
/**
 * @brief The Pitch struct
 */
struct Pitch {
  // grass texture
  sf::Sprite grass;

  // pitch entity
  int entity;

  // texture for drawing lines on and providing to sprite
  sf::RenderTexture tex;

  // pitch lines etc
  PitchDimensions dimensions;
};
/**
 * @brief init the pitch
 */
void init_pitch(Pitch &pitch, const std::string &grass_spritesheet,
                Camera &camera);
/**
 * @brief update_pitch
 * @param pitch
 */
void update_pitch(Pitch &pitch, Camera &camera);
