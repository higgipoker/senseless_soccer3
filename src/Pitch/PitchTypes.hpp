#pragma once
//
#include "Engine/ArcShape.hpp"
//
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/System/Vector3.hpp>
namespace Senseless {
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
struct PitchDrawShapes {
    // origin in screen space
    sf::Vector3f origin;
    // pitch lines
    sf::RectangleShape bounds;
    sf::RectangleShape draw_bounds_north;
    sf::RectangleShape draw_bounds_south;
    sf::RectangleShape box_6;
    sf::RectangleShape box_18;
    sf::ArcShape arc_18;
    sf::RectangleShape halfway_line;
    sf::CircleShape center_circle;
    sf::CircleShape center_spot;
    sf::CircleShape penalty_spot;

    std::vector<sf::Shape *> all_lines;

    PitchDrawShapes() {
        all_lines.push_back(&bounds);
        all_lines.push_back(&box_6);
        all_lines.push_back(&box_18);
        all_lines.push_back(&halfway_line);
        all_lines.push_back(&center_circle);
        all_lines.push_back(&center_spot);
        all_lines.push_back(&penalty_spot);
        all_lines.push_back(&arc_18);
    }
};

//
//
//
struct PitchDimensions {
    static const size_t NumberPoints = 12;
    sf::Vector3f points[NumberPoints][2];
};
//
// gets rid of a lot of static casts etc to make the main file easier to read
//
#define BYE static_cast<size_t>(PitchPointsOfInterest::Bye)
#define SOUTH static_cast<size_t>(PitchPointOfInterestSide::South)
#define NORTH static_cast<size_t>(PitchPointOfInterestSide::North)
#define WEST static_cast<size_t>(PitchPointsOfInterest::SideWest)
#define EAST static_cast<size_t>(PitchPointsOfInterest::SideEast)
#define SIX static_cast<size_t>(PitchPointsOfInterest::Six)
#define EIGHTEEN static_cast<size_t>(PitchPointsOfInterest::Eighteen)
#define HALFWAY static_cast<size_t>(PitchPointsOfInterest::Halfway)
#define CENTER_CIRCLE_WEST static_cast<size_t>(PitchPointsOfInterest::CentercircleWest)
#define CENTER_CIRCLE_EAST static_cast<size_t>(PitchPointsOfInterest::CentercircleEast)
#define CENTER_SPOT static_cast<size_t>(PitchPointsOfInterest::CenterSpot)
#define PENALTY_SPOT static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)
#define EIGHTEEN_ARC_WEST static_cast<size_t>(PitchPointsOfInterest::EighteenArcWest)
#define EIGHTEEN_ARC_EAST static_cast<size_t>(PitchPointsOfInterest::EighteenArcEast)

}  // namespace Senseless
