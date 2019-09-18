#pragma once

#include "Engine/ArcShape.hpp"
#include "Engine/Drawable.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
//
//
//
namespace sf {
inline Color ChalkWhite{255, 255, 255, 200};
}
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
 * @brief The Pitch class
 */
class Pitch : public Engine::Drawable {
 public:
  /**
   * @brief Pitch
   * @param in_filename
   * @param in_target
   */
  Pitch(const std::string &in_filename, const sf::IntRect in_world_bounds);
  /**
   *
   */
  ~Pitch();
  /**
   * @brief create
   */
  void create();
  /**
   * @brief draw
   * @param target
   * @param states
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 protected:
  /// the repeatig grass sprite
  sf::Sprite grass;
  /// pitch sprite
  sf::Sprite pitch;
  /// a texture to render the grass and lines to
  sf::RenderTexture *pitch_texture;
  /// pitch dimensions
  PitchDimensions dimensions;

 private:
  /**
   * @brief init_bounds
   * @param pitch
   */
  void init_bounds();
  /**
   * @brief init_6_yard_boxes
   * @param pitch
   */
  void init_6_yard_boxes();
  /**
   * @brief init_18_yard_boxes
   * @param pitch
   */
  void init_18_yard_boxes();
  /**
   * @brief init_center_circle
   * @param pitch
   */
  void init_center_circle();
  /**
   * @brief init_center_spot
   * @param pitch
   */
  void init_center_spot();
  /**
   * @brief init_penalty_spots
   * @param pitch
   */
  void init_penalty_spots();
  /**
   * @brief init_north_arc
   * @param pitch
   */
  void init_north_arc();
  /**
   * @brief init_south_arc
   * @param pitch
   */
  void init_south_arc();
  /**
   * @brief init_halfway_line
   * @param pitch
   */
  void init_halfway_line();
};
