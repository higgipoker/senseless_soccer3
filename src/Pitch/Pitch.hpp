#pragma once

#include "Engine/ArcShape.hpp"
#include "Engine/Sprite.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <vector>
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

  std::vector<sf::Shape *> all_lines;

  PitchDimensions() {
    all_lines.push_back(&bounds);
    all_lines.push_back(&north_6);
    all_lines.push_back(&north_18);
    all_lines.push_back(&south_6);
    all_lines.push_back(&south_18);
    all_lines.push_back(&halfway_line);
    all_lines.push_back(&center_circle);
    all_lines.push_back(&center_spot);
    all_lines.push_back(&north_penalty_spot);
    all_lines.push_back(&south_penalty_spot);
    all_lines.push_back(&north_arc);
    all_lines.push_back(&south_arc);
  }
};
/**
 * @brief The Pitch class
 */
class Pitch : public Engine::Sprite {
 public:
  //
  //
  //
  Pitch(std::shared_ptr<sf::Texture> in_texture,
        const sf::IntRect in_world_bounds);
  //
  //
  //
  ~Pitch();
  //
  //
  //
  void create();
  //
  //
  //
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  //
  //
  //
  virtual void perspectivize(const float in_camera_height) override;

 protected:
  /// the repeatig grass sprite
  sf::Sprite grass;
  /// pitch sprite
  sf::Sprite pitch;
  /// a texture to render the grass and lines to
  std::unique_ptr<sf::RenderTexture> pitch_texture =
      std::make_unique<sf::RenderTexture>();
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
