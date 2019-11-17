#pragma once
//
#include "PitchSprite.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
//
//
//
class MiniMap : public PitchSprite {
   public:
    //
    //
    //
    MiniMap();
    //
    //
    //
    sf::FloatRect getGlobalBounds() const override;
    //
    //
    //
    virtual void init(const sf::FloatRect in_bounds, const PitchDrawDimensions &in_dimensions,
                      const std::string &in_grass_texture = "") override;
    //
    //
    //
    void updatePlayerPositions(const std::vector<Engine::Vector3> &in_positions, const Engine::Vector3 in_ball_position);
    //
    //
    //
    void setScale(float in_scale_factor);
    //
    //
    //
   protected:
    //
    //
    //
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    //
    //
    //
   private:
    float scale_factor = 0.1F;

    // pitch lines
    sf::Vertex bounds[8];
    sf::Vertex north_6_box[6];
    sf::Vertex north_18_box[6];
    sf::Vertex south_6_box[6];
    sf::Vertex south_18_box[6];
    sf::Vertex halfwayline[2];
    sf::CircleShape center_circle;
    sf::CircleShape ball;

    // players
    sf::Vertex players[20];
    sf::CircleShape circles[20];

    std::vector<sf::Vertex> vlines;
};
