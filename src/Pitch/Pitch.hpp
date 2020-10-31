#pragma once
#include "PitchSprite.hpp"
#include "PitchTypes.hpp"
//
#include "Engine/Entity.hpp"
#include "Engine/Line.hpp"
//
namespace Senseless {
class Pitch : public Entity {
public:
    Pitch (const std::string &in_grass_texture);

    void                        update (const float in_dt) override;
    sf::Vector3f                     getPointOfInterest (const PitchPointsOfInterest in_which,
                                                         const PitchPointOfInterestSide in_side = PitchPointOfInterestSide::South) const;

    const PitchDrawShapes  &getDimensions() const {
        return draw_shapes;
    }

    Line northLine() {
        return north + movable.position;
    }
    Line southLine() {
        return south + movable.position;
    }
    Line eastLine() {
        return east + movable.position;
    }
    Line westLine() {
        return west + movable.position;
    }

private:
    PitchDrawShapes draw_shapes;
    PitchDimensions dimensions;

    void init_bounds();
    void init_6_yard_boxes();
    void init_18_yard_boxes();
    void init_center_circle();
    void init_center_spot();
    void init_penalty_spots();
    void init_penalty_arc();
    void init_halfway_line();

    // for easy reference
    Line north, south, east, west;
};
}  // namespace Senseless
