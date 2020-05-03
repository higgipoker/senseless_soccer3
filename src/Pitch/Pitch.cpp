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
//
const int StandardLineThickness = 2;
const int BorderLineThickness = 1;
//
//
//
Pitch::Pitch(const std::string& in_grass_texture) {
  draw_dimensions.origin = {100, 100};
  init_bounds();
  init_halfway_line();
  init_center_circle();
  init_center_spot();
  init_penalty_spots();
  init_6_yard_boxes();
  init_18_yard_boxes();
  init_south_arc();
  // the sprite
  sprite = std::make_unique<PitchSprite>();
  static_cast<PitchSprite*>(sprite.get())->init(draw_dimensions, in_grass_texture);
  movable.position = draw_dimensions.origin;
}
//
//
//
Vector3 Pitch::toScreenSpace(const Vector3& in_vector) const {
  return {in_vector.x + draw_dimensions.origin.x,
          draw_dimensions.origin.y + draw_dimensions.bounds.getSize().y - in_vector.y};
}
//
//
//
Vector3 Pitch::toPitchSpace(const Vector3& in_vector) const {
  return {in_vector.x - draw_dimensions.origin.x, in_vector.y - draw_dimensions.origin.y};
}
//
//
//
void Pitch::init_bounds() {
  draw_dimensions.bounds.setFillColor(sf::Color::Transparent);
  draw_dimensions.bounds.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.bounds.setOutlineThickness(BorderLineThickness);
  draw_dimensions.bounds.setSize({MetersToPixels(69), MetersToPixels(105)});
  draw_dimensions.bounds.setPosition(BorderLineThickness, BorderLineThickness);

  draw_dimensions.draw_bounds_north.setFillColor(sf::Color::Transparent);
  draw_dimensions.draw_bounds_north.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.draw_bounds_north.setOutlineThickness(BorderLineThickness);
  draw_dimensions.draw_bounds_north.setSize({MetersToPixels(69), MetersToPixels(105)});
  draw_dimensions.draw_bounds_north.setPosition(BorderLineThickness, BorderLineThickness);
  draw_dimensions.draw_bounds_north.setSize({draw_dimensions.draw_bounds_north.getSize().x,
                                             draw_dimensions.draw_bounds_north.getSize().y / 2});

  draw_dimensions.draw_bounds_south.setFillColor(sf::Color::Transparent);
  draw_dimensions.draw_bounds_south.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.draw_bounds_south.setOutlineThickness(BorderLineThickness);
  draw_dimensions.draw_bounds_south.setSize({MetersToPixels(69), MetersToPixels(105)});
  draw_dimensions.draw_bounds_south.setPosition(-BorderLineThickness, -BorderLineThickness);
  draw_dimensions.draw_bounds_south.setSize({draw_dimensions.draw_bounds_south.getSize().x,
                                             draw_dimensions.draw_bounds_south.getSize().y / 2});

  dimensions.points[BYE][SOUTH] = {0, 0};
  dimensions.points[BYE][NORTH] = {0, MetersToPixels(105)};

  dimensions.points[WEST][SOUTH] = {0, 0};
  dimensions.points[WEST][NORTH] = {0, 0};

  dimensions.points[EAST][SOUTH] = {MetersToPixels(69), 0};
  dimensions.points[EAST][NORTH] = {MetersToPixels(69), 0};
}
//
//
//
void Pitch::init_6_yard_boxes() {
  float w = MetersToPixels(18.32f);
  float h = MetersToPixels(5.5f);
  draw_dimensions.box_6.setSize({w, h});
  draw_dimensions.box_6.setFillColor(sf::Color::Transparent);
  draw_dimensions.box_6.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.box_6.setOutlineThickness(StandardLineThickness);
  float x = (draw_dimensions.bounds.getSize().x / 2) - (draw_dimensions.box_6.getSize().x / 2);
  float y = draw_dimensions.bounds.getSize().y - draw_dimensions.box_6.getSize().y;
  draw_dimensions.box_6.setPosition({x, y});

  dimensions.points[SIX][SOUTH] = {x, h};
  dimensions.points[SIX][NORTH] = {x, dimensions.points[BYE][NORTH].y - h};
}
//
//
//
void Pitch::init_18_yard_boxes() {
  float w = MetersToPixels(40.32f);
  float h = MetersToPixels(16.5f);
  draw_dimensions.box_18.setSize({w, h});
  draw_dimensions.box_18.setFillColor(sf::Color::Transparent);
  draw_dimensions.box_18.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.box_18.setOutlineThickness(StandardLineThickness);
  float x = (draw_dimensions.bounds.getSize().x / 2) - (draw_dimensions.box_18.getSize().x / 2);
  float y = draw_dimensions.bounds.getSize().y - draw_dimensions.box_18.getSize().y;
  draw_dimensions.box_18.setPosition({x, y});

  dimensions.points[EIGHTEEN][SOUTH] = {x, h};
  dimensions.points[EIGHTEEN][NORTH] = {x, dimensions.points[BYE][NORTH].y - h};
}
//
//
//
void Pitch::init_halfway_line() {
  draw_dimensions.halfway_line.setSize({draw_dimensions.bounds.getSize().x, 2});
  draw_dimensions.halfway_line.setFillColor(sf::ChalkWhite);
  float x = 0;
  float y = draw_dimensions.bounds.getSize().y / 2;
  draw_dimensions.halfway_line.setPosition({x, y});

  dimensions.points[HALFWAY][SOUTH] = {x, y};
  dimensions.points[HALFWAY][NORTH] = {x, y};
}
//
//
//
void Pitch::init_center_circle() {
  draw_dimensions.center_circle.setPointCount(60);
  draw_dimensions.center_circle.setRadius(MetersToPixels(9.15f));
  draw_dimensions.center_circle.setFillColor(sf::Color::Transparent);
  draw_dimensions.center_circle.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.center_circle.setOutlineThickness(StandardLineThickness);
  draw_dimensions.center_circle.setCenter(
      {draw_dimensions.bounds.getSize().x / 2, draw_dimensions.bounds.getSize().y / 2});

  dimensions.points[CENTER_CIRCLE_WEST][SOUTH] = {
      draw_dimensions.bounds.getSize().x / 2 - draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
  dimensions.points[CENTER_CIRCLE_WEST][NORTH] = {
      draw_dimensions.bounds.getSize().x / 2 - draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};

  dimensions.points[CENTER_CIRCLE_EAST][SOUTH] = {
      draw_dimensions.bounds.getSize().x / 2 + draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
  dimensions.points[CENTER_CIRCLE_EAST][NORTH] = {
      draw_dimensions.bounds.getSize().x / 2 + draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
}
//
//
//
void Pitch::init_center_spot() {
  draw_dimensions.center_spot.setRadius(MetersToPixels(0.2f));
  draw_dimensions.center_spot.setFillColor(sf::ChalkWhite);
  draw_dimensions.center_spot.setCenter(
      {draw_dimensions.bounds.getSize().x / 2, draw_dimensions.bounds.getSize().y / 2});

  dimensions.points[CENTER_SPOT][SOUTH] = {draw_dimensions.bounds.getSize().x / 2,
                                           draw_dimensions.bounds.getSize().y / 2};

  dimensions.points[CENTER_SPOT][NORTH] = {draw_dimensions.bounds.getSize().x / 2,
                                           draw_dimensions.bounds.getSize().y / 2};
}
//
//
//
void Pitch::init_penalty_spots() {
  draw_dimensions.penalty_spot.setRadius(MetersToPixels(0.2f));
  draw_dimensions.penalty_spot.setFillColor(sf::ChalkWhite);
  float x = draw_dimensions.bounds.getSize().x / 2;
  float y = draw_dimensions.bounds.getSize().y - MetersToPixels(10.9f);
  draw_dimensions.penalty_spot.setPosition({x, y});

  dimensions.points[PENALTY_SPOT][SOUTH] = {x, y};
  dimensions.points[PENALTY_SPOT][SOUTH] = {x, draw_dimensions.bounds.getSize().y - y};
}
//
//
//
void Pitch::init_south_arc() {
  draw_dimensions.arc_18.setPointCount(60);
  draw_dimensions.arc_18.setRadius(MetersToPixels(7.f));
  draw_dimensions.arc_18.setFillColor(sf::Color::Transparent);
  draw_dimensions.arc_18.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.arc_18.setOutlineThickness(StandardLineThickness);
  draw_dimensions.arc_18.setOrigin(
      {draw_dimensions.arc_18.getRadius(), draw_dimensions.arc_18.getRadius()});
  draw_dimensions.arc_18.setRotation(-90);
  float x = draw_dimensions.bounds.getSize().x / 2;
  float y = draw_dimensions.bounds.getSize().y - draw_dimensions.box_18.getSize().y - 2;
  draw_dimensions.arc_18.setPosition({x, y});

  dimensions.points[EIGHTEEN_ARC_WEST][SOUTH] = {
      dimensions.points[PENALTY_SPOT][SOUTH].x - draw_dimensions.arc_18.getRadius(),
      dimensions.points[PENALTY_SPOT][SOUTH].y};

  dimensions.points[EIGHTEEN_ARC_EAST][SOUTH] = {
      dimensions.points[PENALTY_SPOT][SOUTH].x + draw_dimensions.arc_18.getRadius(),
      dimensions.points[PENALTY_SPOT][SOUTH].y};
}
//
//
//
void Pitch::update() {
  static_cast<PitchSprite*>(sprite.get())->setPosition(movable.position.x, movable.position.y);
}
//
//
//
Vector3 Pitch::getPointOfInterest(const PitchPointsOfInterest in_which,
                                             const PitchPointOfInterestSide in_side) const {
  return dimensions.points[static_cast<size_t>(in_which)][static_cast<size_t>(in_side)];
}
}  // namespace Senseless
