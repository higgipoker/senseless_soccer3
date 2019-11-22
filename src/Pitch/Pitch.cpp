#include "Pitch.hpp"
//
#include "Engine/Metrics.hpp"
#include "Engine/Vector.hpp"
//
using namespace Engine;
//
//
//
namespace sf {
inline Color ChalkWhite{210, 210, 210, 255};
}
//
const int StandardLineThickness = 2;
const int BorderLineThickness = 1;
//
//
//
Pitch::Pitch(const std::string& in_grass_texture, const sf::FloatRect in_bounds)
    : minimap_entity(std::move(minimap)) {
  // tmp test
  draw_dimensions.origin = {200, 200};

  // pitch bounds
  init_bounds();

  // halfway line
  init_halfway_line();

  // center circle
  init_center_circle();

  // center spot
  init_center_spot();

  // pen spots
  init_penalty_spots();

  // 6 yard boxes
  init_6_yard_boxes();

  // 18 yard boxes
  init_18_yard_boxes();

  // north arc
  init_south_arc();

  // the sprite
  sprite.init(in_bounds, draw_dimensions, in_grass_texture);

  // minimap is a pitch sprite with no grass texture
  static_cast<MiniMap*>(&minimap_entity.getSprite())
      ->init(in_bounds, draw_dimensions);
  minimap_entity.movable.name = "mini map";
  minimap_entity.movable.position = {10, 10};

  movable.position = draw_dimensions.origin;
}
//
//
//
Engine::Sprite& Pitch::getSprite() { return sprite; }
//
//
//
Engine::Sprite& Pitch::getMiniMap() { return minimap_entity.getSprite(); }
//
//
//
Vector3 Pitch::toScreenSpace(const Vector3& in_vector) const {
  return {in_vector.x + draw_dimensions.origin.x,
          draw_dimensions.origin.y + draw_dimensions.bounds.getSize().y -
              in_vector.y};
}
//
//
//
Vector3 Pitch::toPitchSpace(const Vector3& in_vector) const {
  float origin = draw_dimensions.origin.y;
  float height = draw_dimensions.bounds.getSize().y;
  return {in_vector.x - draw_dimensions.origin.x,
          origin + height - in_vector.y};
}
//
//
//
void Pitch::init_bounds() {
  draw_dimensions.bounds.setFillColor(sf::Color::Transparent);
  draw_dimensions.bounds.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.bounds.setOutlineThickness(BorderLineThickness);
  draw_dimensions.bounds.setSize(
      sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                   static_cast<float>(Metrics::MetersToPixels(105))));
  draw_dimensions.bounds.setPosition(BorderLineThickness, BorderLineThickness);

  draw_dimensions.draw_bounds_north.setFillColor(sf::Color::Transparent);
  draw_dimensions.draw_bounds_north.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.draw_bounds_north.setOutlineThickness(BorderLineThickness);
  draw_dimensions.draw_bounds_north.setSize(
      sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                   static_cast<float>(Metrics::MetersToPixels(105))));
  draw_dimensions.draw_bounds_north.setPosition(BorderLineThickness,
                                                BorderLineThickness);
  draw_dimensions.draw_bounds_north.setSize(
      {draw_dimensions.draw_bounds_north.getSize().x,
       draw_dimensions.draw_bounds_north.getSize().y / 2});

  draw_dimensions.draw_bounds_south.setFillColor(sf::Color::Transparent);
  draw_dimensions.draw_bounds_south.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.draw_bounds_south.setOutlineThickness(BorderLineThickness);
  draw_dimensions.draw_bounds_south.setSize(
      sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                   static_cast<float>(Metrics::MetersToPixels(105))));
  draw_dimensions.draw_bounds_south.setPosition(-BorderLineThickness,
                                                -BorderLineThickness);
  draw_dimensions.draw_bounds_south.setSize(
      {draw_dimensions.draw_bounds_south.getSize().x,
       draw_dimensions.draw_bounds_south.getSize().y / 2});

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Bye)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {0,
                                                                             0};
  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Bye)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      0, static_cast<float>(Metrics::MetersToPixels(105))};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::SideWest)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {0,
                                                                             0};
  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::SideWest)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {0,
                                                                             0};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::SideEast)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      static_cast<float>(Metrics::MetersToPixels(69)), 0};
  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::SideEast)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      static_cast<float>(Metrics::MetersToPixels(69)), 0};
}
//
//
//
void Pitch::init_6_yard_boxes() {
  float w = static_cast<float>(Metrics::MetersToPixels(18.32f));
  float h = static_cast<float>(Metrics::MetersToPixels(5.5f));
  draw_dimensions.south_6.setSize(sf::Vector2f(w, h));
  draw_dimensions.south_6.setFillColor(sf::Color::Transparent);
  draw_dimensions.south_6.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.south_6.setOutlineThickness(StandardLineThickness);
  float x = (draw_dimensions.bounds.getSize().x / 2) -
            (draw_dimensions.south_6.getSize().x / 2);
  float y =
      draw_dimensions.bounds.getSize().y - draw_dimensions.south_6.getSize().y;
  draw_dimensions.south_6.setPosition(sf::Vector2f(x, y));

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Six)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {x,
                                                                             h};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Six)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      x, dimensions
                 .points[static_cast<size_t>(PitchPointsOfInterest::Bye)]
                        [static_cast<size_t>(PitchPointOfInterestSide::North)]
                 .y -
             h};
}
//
//
//
void Pitch::init_18_yard_boxes() {
  float w = static_cast<float>(Metrics::MetersToPixels(40.32f));
  float h = static_cast<float>(Metrics::MetersToPixels(16.5f));
  draw_dimensions.south_18.setSize(sf::Vector2f(w, h));
  draw_dimensions.south_18.setFillColor(sf::Color::Transparent);
  draw_dimensions.south_18.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.south_18.setOutlineThickness(StandardLineThickness);
  float x = (draw_dimensions.bounds.getSize().x / 2) -
            (draw_dimensions.south_18.getSize().x / 2);
  float y =
      draw_dimensions.bounds.getSize().y - draw_dimensions.south_18.getSize().y;
  draw_dimensions.south_18.setPosition(sf::Vector2f(x, y));

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Eighteen)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {x,
                                                                             h};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Eighteen)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      x, dimensions
                 .points[static_cast<size_t>(PitchPointsOfInterest::Bye)]
                        [static_cast<size_t>(PitchPointOfInterestSide::North)]
                 .y -
             h};
}
//
//
//
void Pitch::init_halfway_line() {
  draw_dimensions.halfway_line.setSize({draw_dimensions.bounds.getSize().x, 2});
  draw_dimensions.halfway_line.setFillColor(sf::ChalkWhite);
  float x = 0;
  float y = draw_dimensions.bounds.getSize().y / 2;
  draw_dimensions.halfway_line.setPosition(sf::Vector2f(x, y));

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Halfway)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {x,
                                                                             y};
  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::Halfway)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {x,
                                                                             y};
}
//
//
//
void Pitch::init_center_circle() {
  draw_dimensions.center_circle.setPointCount(60);
  draw_dimensions.center_circle.setRadius(
      static_cast<float>(Metrics::MetersToPixels(9.15f)));
  draw_dimensions.center_circle.setFillColor(sf::Color::Transparent);
  draw_dimensions.center_circle.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.center_circle.setOutlineThickness(StandardLineThickness);
  draw_dimensions.center_circle.setCenter(
      {draw_dimensions.bounds.getSize().x / 2,
       draw_dimensions.bounds.getSize().y / 2});

  dimensions
      .points[static_cast<size_t>(PitchPointsOfInterest::CentercircleWest)]
             [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      draw_dimensions.bounds.getSize().x / 2 -
          draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
  dimensions
      .points[static_cast<size_t>(PitchPointsOfInterest::CentercircleWest)]
             [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      draw_dimensions.bounds.getSize().x / 2 -
          draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};

  dimensions
      .points[static_cast<size_t>(PitchPointsOfInterest::CentercircleEast)]
             [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      draw_dimensions.bounds.getSize().x / 2 +
          draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
  dimensions
      .points[static_cast<size_t>(PitchPointsOfInterest::CentercircleEast)]
             [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      draw_dimensions.bounds.getSize().x / 2 +
          draw_dimensions.center_circle.getRadius(),
      draw_dimensions.bounds.getSize().x / 2};
}
//
//
//
void Pitch::init_center_spot() {
  draw_dimensions.center_spot.setRadius(
      static_cast<float>(Metrics::MetersToPixels(0.2f)));
  draw_dimensions.center_spot.setFillColor(sf::ChalkWhite);
  draw_dimensions.center_spot.setCenter(
      {draw_dimensions.bounds.getSize().x / 2,
       draw_dimensions.bounds.getSize().y / 2});

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::CenterSpot)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      draw_dimensions.bounds.getSize().x / 2,
      draw_dimensions.bounds.getSize().y / 2};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::CenterSpot)]
                   [static_cast<size_t>(PitchPointOfInterestSide::North)] = {
      draw_dimensions.bounds.getSize().x / 2,
      draw_dimensions.bounds.getSize().y / 2};
}
//
//
//
void Pitch::init_penalty_spots() {
  draw_dimensions.south_penalty_spot.setRadius(
      static_cast<float>(Metrics::MetersToPixels(0.2f)));
  draw_dimensions.south_penalty_spot.setFillColor(sf::ChalkWhite);
  float x = draw_dimensions.bounds.getSize().x / 2;
  float y = draw_dimensions.bounds.getSize().y - Metrics::MetersToPixels(10.9f);
  draw_dimensions.south_penalty_spot.setPosition(sf::Vector2f(x, y));

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {x,
                                                                             y};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      x, draw_dimensions.bounds.getSize().y - y};
}
//
//
//
void Pitch::init_south_arc() {
  draw_dimensions.south_arc.setPointCount(60);
  draw_dimensions.south_arc.setRadius(
      static_cast<float>(Metrics::MetersToPixels(7.f)));
  draw_dimensions.south_arc.setFillColor(sf::Color::Transparent);
  draw_dimensions.south_arc.setOutlineColor(sf::ChalkWhite);
  draw_dimensions.south_arc.setOutlineThickness(StandardLineThickness);
  draw_dimensions.south_arc.setOrigin(
      sf::Vector2f(draw_dimensions.south_arc.getRadius(),
                   draw_dimensions.south_arc.getRadius()));
  draw_dimensions.south_arc.setRotation(-90);
  float x = draw_dimensions.bounds.getSize().x / 2;
  float y = draw_dimensions.bounds.getSize().y -
            draw_dimensions.south_18.getSize().y - 2;
  draw_dimensions.south_arc.setPosition(sf::Vector2f(x, y));

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::EighteenArcWest)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      dimensions
              .points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                     [static_cast<size_t>(PitchPointOfInterestSide::South)]
              .x -
          draw_dimensions.south_arc.getRadius(),
      dimensions
          .points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                 [static_cast<size_t>(PitchPointOfInterestSide::South)]
          .y};

  dimensions.points[static_cast<size_t>(PitchPointsOfInterest::EighteenArcEast)]
                   [static_cast<size_t>(PitchPointOfInterestSide::South)] = {
      dimensions
              .points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                     [static_cast<size_t>(PitchPointOfInterestSide::South)]
              .x +
          draw_dimensions.south_arc.getRadius(),
      dimensions
          .points[static_cast<size_t>(PitchPointsOfInterest::PenaltySpot)]
                 [static_cast<size_t>(PitchPointOfInterestSide::South)]
          .y};
}
//
//
//
void Pitch::update() {
  sprite.setPosition(movable.position.x, movable.position.y);
  minimap_entity.update();
}
//
//
//
Engine::Vector3 Pitch::getPointOfInterest(
    const PitchPointsOfInterest in_which,
    const PitchPointOfInterestSide in_side) const {
  return dimensions
      .points[static_cast<size_t>(in_which)][static_cast<size_t>(in_side)];
}
