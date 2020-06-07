#include "Pitch.hpp"
//
#include "PitchTypes.hpp"
//
#include "Engine/Metrics.hpp"
#include "Engine/Vector.hpp"
//
namespace sf {
inline Color ChalkWhite{210, 210, 210, 255};
}
namespace Senseless {
// todo varialbe pitch sizes
static const float PITCH_WIDTH = MetersToPixels(69);
static const float PITCH_LENGTH = MetersToPixels(105);
static const float SIX_YARD_BOX_WIDTH = MetersToPixels(18.32f);
static const float SIX_YARD_BOX_LENGTH = MetersToPixels(5.5f);
static const float EIGHTEEN_YARD_BOX_WIDTH = MetersToPixels(40.32f);
static const float EIGHTEEN_YARD_BOX_LENGTH = MetersToPixels(16.5f);
static const float PENALTY_SPOT_LENTGH = MetersToPixels(10.9f);
//
const int StandardLineThickness = 2;
const int BorderLineThickness = 1;
//
//
//
Pitch::Pitch(const std::string &in_grass_texture) : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()) {
    type = EntityType::Pitch;
    name = "pitch";
    draw_shapes.origin = {250, 250};
    init_bounds();
    init_halfway_line();
    init_center_circle();
    init_center_spot();
    init_penalty_spots();
    init_6_yard_boxes();
    init_18_yard_boxes();
    init_penalty_arc();
    // the sprite
    renderable.sprite = std::make_unique<PitchSprite>();
    static_cast<PitchSprite *>(renderable.sprite.get())->init(draw_shapes, in_grass_texture);
    movable.position = draw_shapes.origin;
}
//
//
//
void Pitch::init_bounds() {
    //
    // for drawing
    //
    draw_shapes.bounds.setFillColor(sf::Color::Transparent);
    draw_shapes.bounds.setOutlineColor(sf::ChalkWhite);
    draw_shapes.bounds.setOutlineThickness(BorderLineThickness);
    draw_shapes.bounds.setSize({PITCH_WIDTH, PITCH_LENGTH});
    draw_shapes.bounds.setPosition(BorderLineThickness, BorderLineThickness);

    draw_shapes.draw_bounds_north.setFillColor(sf::Color::Transparent);
    draw_shapes.draw_bounds_north.setOutlineColor(sf::ChalkWhite);
    draw_shapes.draw_bounds_north.setOutlineThickness(BorderLineThickness);
    draw_shapes.draw_bounds_north.setSize({PITCH_WIDTH, PITCH_LENGTH});
    draw_shapes.draw_bounds_north.setPosition(BorderLineThickness, BorderLineThickness);
    draw_shapes.draw_bounds_north.setSize({draw_shapes.draw_bounds_north.getSize().x,
                                           draw_shapes.draw_bounds_north.getSize().y / 2});

    draw_shapes.draw_bounds_south.setFillColor(sf::Color::Transparent);
    draw_shapes.draw_bounds_south.setOutlineColor(sf::ChalkWhite);
    draw_shapes.draw_bounds_south.setOutlineThickness(BorderLineThickness);
    draw_shapes.draw_bounds_south.setSize({PITCH_WIDTH, PITCH_LENGTH});
    draw_shapes.draw_bounds_south.setPosition(-BorderLineThickness, -BorderLineThickness);
    draw_shapes.draw_bounds_south.setSize({draw_shapes.draw_bounds_south.getSize().x,
                                           draw_shapes.draw_bounds_south.getSize().y / 2});

    //
    // for points ofinterest
    //
    dimensions.points[BYE][NORTH] = {0, 0};
    dimensions.points[BYE][SOUTH] = {0, PITCH_LENGTH};

    dimensions.points[WEST][NORTH] = {0, 0};
    dimensions.points[WEST][SOUTH] = {0, 0};

    dimensions.points[EAST][NORTH] = {PITCH_WIDTH, 0};
    dimensions.points[EAST][SOUTH] = {PITCH_WIDTH, 0};
}
//
//
//
void Pitch::init_6_yard_boxes() {
    //
    // for drawing
    //
    float x = (draw_shapes.bounds.getSize().x / 2) - SIX_YARD_BOX_WIDTH / 2;
    float y = draw_shapes.bounds.getPosition().y;
    draw_shapes.box_6.setSize({SIX_YARD_BOX_WIDTH, SIX_YARD_BOX_LENGTH});
    draw_shapes.box_6.setPosition({x, y});
    draw_shapes.box_6.setFillColor(sf::Color::Transparent);
    draw_shapes.box_6.setOutlineColor(sf::ChalkWhite);
    draw_shapes.box_6.setOutlineThickness(StandardLineThickness);
    //
    // for points of interest
    //
    dimensions.points[SIX][NORTH] = {x, y + SIX_YARD_BOX_LENGTH};
    dimensions.points[SIX][SOUTH] = {x, dimensions.points[SIX][NORTH].y + (draw_shapes.bounds.getSize().y - SIX_YARD_BOX_LENGTH*2)};
}
//
//
//
void Pitch::init_18_yard_boxes() {
    float x = (draw_shapes.bounds.getSize().x / 2) - EIGHTEEN_YARD_BOX_WIDTH / 2;
    float y = draw_shapes.bounds.getPosition().y;
    draw_shapes.box_18.setSize({EIGHTEEN_YARD_BOX_WIDTH, EIGHTEEN_YARD_BOX_LENGTH});
    draw_shapes.box_18.setFillColor(sf::Color::Transparent);
    draw_shapes.box_18.setOutlineColor(sf::ChalkWhite);
    draw_shapes.box_18.setOutlineThickness(StandardLineThickness);
    draw_shapes.box_18.setPosition({x, y});

    dimensions.points[EIGHTEEN][NORTH] = {x, y + EIGHTEEN_YARD_BOX_LENGTH};
    dimensions.points[EIGHTEEN][SOUTH] = {x, dimensions.points[EIGHTEEN][NORTH].y + (draw_shapes.bounds.getSize().y - EIGHTEEN_YARD_BOX_LENGTH*2)};
}
//
//
//
void Pitch::init_halfway_line() {
    draw_shapes.halfway_line.setSize({draw_shapes.bounds.getSize().x, 2});
    draw_shapes.halfway_line.setFillColor(sf::ChalkWhite);
    float x = 0;
    float y = draw_shapes.bounds.getSize().y / 2;
    draw_shapes.halfway_line.setPosition({x, y});

    dimensions.points[HALFWAY][NORTH] = {x, y};
    dimensions.points[HALFWAY][SOUTH] = {x, y};
}
//
//
//
void Pitch::init_center_circle() {
    draw_shapes.center_circle.setPointCount(60);
    draw_shapes.center_circle.setRadius(MetersToPixels(9.15f));
    draw_shapes.center_circle.setFillColor(sf::Color::Transparent);
    draw_shapes.center_circle.setOutlineColor(sf::ChalkWhite);
    draw_shapes.center_circle.setOutlineThickness(StandardLineThickness);
    draw_shapes.center_circle.setCenter(
    {draw_shapes.bounds.getSize().x / 2, draw_shapes.bounds.getSize().y / 2});

    dimensions.points[CENTER_CIRCLE_WEST][NORTH] = {
        draw_shapes.bounds.getSize().x / 2 - draw_shapes.center_circle.getRadius(),
        draw_shapes.bounds.getSize().x / 2 - draw_shapes.center_circle.getRadius()
    };
    dimensions.points[CENTER_CIRCLE_WEST][SOUTH] = {
        draw_shapes.bounds.getSize().x / 2 - draw_shapes.center_circle.getRadius(),
        draw_shapes.bounds.getSize().x / 2 + draw_shapes.center_circle.getRadius()
    };
    dimensions.points[CENTER_CIRCLE_EAST][NORTH] = {
        draw_shapes.bounds.getSize().x / 2 + draw_shapes.center_circle.getRadius(),
        draw_shapes.bounds.getSize().x / 2 - draw_shapes.center_circle.getRadius()
    };
    dimensions.points[CENTER_CIRCLE_EAST][SOUTH] = {
        draw_shapes.bounds.getSize().x / 2 + draw_shapes.center_circle.getRadius(),
        draw_shapes.bounds.getSize().x / 2 + draw_shapes.center_circle.getRadius()
    };
}
//
//
//
void Pitch::init_center_spot() {
    draw_shapes.center_spot.setRadius(MetersToPixels(0.2f));
    draw_shapes.center_spot.setFillColor(sf::ChalkWhite);
    draw_shapes.center_spot.setCenter(
    {draw_shapes.bounds.getSize().x / 2, draw_shapes.bounds.getSize().y / 2});

    dimensions.points[CENTER_SPOT][NORTH] = dimensions.points[CENTER_SPOT][SOUTH] = {draw_shapes.bounds.getSize().x / 2,
                                                                                     draw_shapes.bounds.getSize().y / 2                                                                                };
}
//
//
//
void Pitch::init_penalty_spots() {
    float x = draw_shapes.bounds.getSize().x / 2;
    float y = draw_shapes.bounds.getPosition().y + PENALTY_SPOT_LENTGH;
    draw_shapes.penalty_spot.setRadius(MetersToPixels(0.2f));
    draw_shapes.penalty_spot.setFillColor(sf::ChalkWhite);
    draw_shapes.penalty_spot.setPosition({x, y});

    dimensions.points[PENALTY_SPOT][NORTH] = {x, y};
    dimensions.points[PENALTY_SPOT][SOUTH] = {x, draw_shapes.bounds.getSize().y - y};
}
//
//
//
void Pitch::init_penalty_arc() {
    float x = draw_shapes.bounds.getSize().x / 2;
    float y = draw_shapes.bounds.getPosition().y  + EIGHTEEN_YARD_BOX_LENGTH + 2;
    draw_shapes.arc_18.setPosition({x, y});
    draw_shapes.arc_18.setPointCount(60);
    draw_shapes.arc_18.setRadius(MetersToPixels(7.f));
    draw_shapes.arc_18.setFillColor(sf::Color::Transparent);
    draw_shapes.arc_18.setOutlineColor(sf::ChalkWhite);
    draw_shapes.arc_18.setOutlineThickness(StandardLineThickness);
    draw_shapes.arc_18.setOrigin(
    {draw_shapes.arc_18.getRadius(), draw_shapes.arc_18.getRadius()});
    draw_shapes.arc_18.setRotation(90);    

    dimensions.points[EIGHTEEN_ARC_WEST][NORTH] = {
        dimensions.points[PENALTY_SPOT][NORTH].x - draw_shapes.arc_18.getRadius(),
        dimensions.points[PENALTY_SPOT][NORTH].y
    };

    dimensions.points[EIGHTEEN_ARC_EAST][SOUTH] = {
        dimensions.points[PENALTY_SPOT][SOUTH].x + draw_shapes.arc_18.getRadius(),
        dimensions.points[PENALTY_SPOT][SOUTH].y
    };
}
//
//
//
void Pitch::update(const float in_dt) {
    static_cast<PitchSprite *>(renderable.sprite.get())->setPosition(movable.position.x, movable.position.y);
}
//
//
//
Vector3 Pitch::getPointOfInterest(const PitchPointsOfInterest in_which,
                                  const PitchPointOfInterestSide in_side) const {
    return dimensions.points[static_cast<size_t>(in_which)][static_cast<size_t>(in_side)] + movable.position;
}
}  // namespace Senseless




