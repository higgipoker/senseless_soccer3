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
inline std::string grass_tile{Globals::GFX_FOLDER + grasses.at(1) + ".png"};

namespace sf {
inline Color ChalkWhite{255, 255, 255, 200};

/**
 * @brief The ArcShape struct
 */
struct ArcShape : public CircleShape {
  /**
   * @brief ArcShape
   * @param radius
   * @param pointCount
   */
  ArcShape(float radius = 0, std::size_t pointCount = 30)
      : CircleShape(radius, pointCount) {}

  /**
   * @brief getPointCount
   * @return
   */
  std::size_t getPointCount() const override { return (m_pointCount / 2) + 1; }
};
}  // namespace sf
/**
 * @brief The PitchDimensions struct
 */
struct PitchDimensions {
  // pitch lines
  sf::RectangleShape bounds;
  sf::RectangleShape north_6;
  sf::RectangleShape north_18;
  sf::RectangleShape south_6;
  sf::RectangleShape south_18;
  sf::RectangleShape halfway_line;
  sf::CircleShape center_circle;
  sf::CircleShape center_spot;
  sf::CircleShape north_penalty_spot;
  sf::CircleShape south_penalty_spot;
  sf::ArcShape north_arc;
  sf::ArcShape south_arc;
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
 * @brief init_bounds
 * @param pitch
 */
void init_bounds(Pitch &pitch);
/**
 * @brief init_6_yard_boxes
 * @param pitch
 */
void init_6_yard_boxes(Pitch &pitch);
/**
 * @brief init_18_yard_boxes
 * @param pitch
 */
void init_18_yard_boxes(Pitch &pitch);
/**
 * @brief init_center_circle
 * @param pitch
 */
void init_center_circle(Pitch &pitch);
/**
 * @brief init_center_spot
 * @param pitch
 */
void init_center_spot(Pitch &pitch);
/**
 * @brief init_penalty_spots
 * @param pitch
 */
void init_penalty_spots(Pitch &pitch);
/**
 * @brief init_north_arc
 * @param pitch
 */
void init_north_arc(Pitch &pitch);
/**
 * @brief init_south_arc
 * @param pitch
 */
void init_south_arc(Pitch &pitch);
/**
 * @brief init_halfway_line
 * @param pitch
 */
void init_halfway_line(Pitch &pitch);
/**
 * @brief update_pitch
 * @param pitch
 */
void update_pitch(Pitch &pitch, Camera &camera);
