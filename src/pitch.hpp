#pragma once
#include "camera.hpp"
#include "grass.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

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
