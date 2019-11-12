#pragma once

#include "Engine/ArcShape.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Types.hpp"
#include "Engine/Vector.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <vector>
/**
 * @brief The PitchDimensions struct
 */
struct PitchDimensions {
    // origin in screen space
    Engine::Vector3 origin;
    // pitch lines
    sf::RectangleShape bounds;
    sf::RectangleShape draw_bounds;
    sf::RectangleShape south_6;
    sf::RectangleShape south_18;
    sf::RectangleShape halfway_line;
    sf::CircleShape center_circle;
    sf::CircleShape center_spot;
    sf::CircleShape south_penalty_spot;
    sf::ArcShape south_arc;

    std::vector<sf::Shape *> all_lines;

    PitchDimensions() {
        all_lines.push_back(&bounds);
        all_lines.push_back(&south_6);
        all_lines.push_back(&south_18);
        all_lines.push_back(&halfway_line);
        all_lines.push_back(&center_circle);
        all_lines.push_back(&center_spot);
        all_lines.push_back(&south_penalty_spot);
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
    Pitch(SharedPtr<sf::Texture> in_texture, const sf::FloatRect in_world_bounds);
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
    Engine::Vector3 toScreenSpace(const Engine::Vector3 &in_vector) const;
    //
    //
    //
    Engine::Vector3 toPitchSpace(const Engine::Vector3 &in_vector) const;
    //
    //
    //
    virtual void perspectivize(const float in_camera_height) override;

    // todo move this out to an pitch entity?
    /// pitch dimensions
    PitchDimensions dimensions;

   protected:
    /// the repeatig grass sprite
    sf::Sprite grass;
    /// pitch sprite
    sf::Sprite pitch;
    /// a texture to render the grass and lines to
    UniquePtr<sf::RenderTexture> pitch_texture = std::make_unique<sf::RenderTexture>();

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
     * @brief init_halfway_line
     * @param pitch
     */
    void init_halfway_line();
    // to flip shapes
    sf::Transform translate;
    sf::Transform flip;
    sf::Transform translate_and_flip;
};
