#pragma once
//
#include "PitchSprite.hpp"
//
#include "Engine/Sprite.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector3.hpp>
namespace Senseless {
class MiniMapSprite : public Sprite {
public:
    MiniMapSprite();
    sf::FloatRect getGlobalBounds() const override;
    void          init(const PitchDrawShapes &in_dimensions);
    void          update(const sf::Vector3f in_pitch_position, const std::vector<sf::Vector3f> &in_positions, const sf::Vector3f in_ball_position, const sf::RectangleShape in_camera);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    // pitch lines
    std::array<sf::Vertex, 8> bounds;
    std::array<sf::Vertex, 6> north_6_box;
    std::array<sf::Vertex, 6> north_18_box;
    std::array<sf::Vertex, 6> south_6_box;
    std::array<sf::Vertex, 6> south_18_box;
    std::array<sf::Vertex, 2> halfwayline;
    sf::CircleShape           center_circle;
    sf::CircleShape           ball;
    sf::RectangleShape        camera;

    // players
    //std::array<sf::Vertex, 20>      players;
    std::array<sf::CircleShape, 20> players;
    std::vector<sf::Vertex>         vlines;
};
}  // namespace Senseless
