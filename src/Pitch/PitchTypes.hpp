#pragma once
//
#include "Engine/ArcShape.hpp"
#include "Engine/Vector.hpp"
//
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
//
//
//
enum class PitchPointsOfInterest : size_t {
    Bye,
    Six,
    Eighteen,
    Halfway,
    CentercircleWest,
    CentercircleEast,
    CenterSpot,
    PenaltySpot,
    SideWest,
    SideEast,
    EighteenArcWest,
    EighteenArcEast
};
enum class PitchPointOfInterestSide : size_t { South, North };
//
//
//
struct PitchDrawDimensions {
    // origin in screen space
    Engine::Vector3 origin;
    // pitch lines
    sf::RectangleShape bounds;
    sf::RectangleShape draw_bounds_north;
    sf::RectangleShape draw_bounds_south;
    sf::RectangleShape south_6;
    sf::RectangleShape south_18;
    sf::RectangleShape halfway_line;
    sf::CircleShape center_circle;
    sf::CircleShape center_spot;
    sf::CircleShape south_penalty_spot;
    sf::ArcShape south_arc;

    std::vector<sf::Shape *> all_lines;

    PitchDrawDimensions() {
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

//
//
//
struct PitchDimensions {
    static const size_t NumberPoints = 12;
    Engine::Vector3 points[NumberPoints][2];
};
