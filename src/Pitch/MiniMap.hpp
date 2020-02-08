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
    void updatePlayerPositions(const std::vector<Engine::Vector3> &in_positions,
                               const Engine::Vector3 in_ball_position);
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
    // pitch lines
    std::array<sf::Vertex, 8> bounds;
    std::array<sf::Vertex, 6> north_6_box;
    std::array<sf::Vertex, 6> north_18_box;
    std::array<sf::Vertex, 6> south_6_box;
    std::array<sf::Vertex, 6> south_18_box;
    std::array<sf::Vertex, 2> halfwayline;
    sf::CircleShape center_circle;
    sf::CircleShape ball;

    // players
    std::array<sf::Vertex, 20> players;
    std::array<sf::CircleShape, 20> circles;

    std::vector<sf::Vertex> vlines;
};
