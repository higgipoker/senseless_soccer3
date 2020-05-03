#pragma once
#include "PitchTypes.hpp"
//
#include "Engine/Sprite.hpp"
#include "Engine/Types.hpp"
//
#include <SFML/Graphics/RenderTexture.hpp>
//
#include <memory>
#include <vector>
namespace Senseless {
/**
 * @brief The Pitch class
 */
class PitchSprite : public Sprite {
 public:
  //
  //
  //
  virtual void init(const PitchDrawDimensions &in_dimensions,
                    const std::string &in_grass_texture = "");
  //
  //
  //
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  //
  //
  //
 protected:
  /// a texture to render the grass and lines to
  sf::RenderTexture pitch_texture;

  // to flip shapes
  sf::Transform flip;
};

}  // namespace Senseless
