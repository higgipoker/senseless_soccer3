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
/**
 * @brief The Pitch class
 */
class PitchSprite : public Engine::Sprite {
   public:
    //
    //
    //
    virtual void init(const sf::FloatRect in_bounds, const PitchDimensions &in_dimensions,
                      const std::string &in_grass_texture = "");
    //
    //
    //
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    //
    //
    //
   protected:
    /// pitch sprite
    sf::Sprite sprite;
    /// a texture to render the grass and lines to
    sf::RenderTexture pitch_texture;

    // to flip shapes
    sf::Transform flip;

};
