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
Pitch::Pitch(const std::string& in_grass_texture, const sf::FloatRect in_bounds) : minimap_entity(std::move(minimap)) {
    // tmp test
    dimensions.origin = {200, 200};

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
    init_north_arc();

    // the sprite
    sprite.init(in_bounds, dimensions, in_grass_texture);

    // minimap is a pitch sprite with no grass texture
    static_cast<MiniMap*>(&minimap_entity.getSprite())->init(in_bounds, dimensions);
    minimap_entity.movable.name = "mini map";
    minimap_entity.movable.position = {10,10};

    movable.position = dimensions.origin;
}
//
//
//
Engine::Sprite& Pitch::getSprite() {
    return sprite;
}
//
//
//
Engine::Sprite& Pitch::getMiniMap() {
    return minimap_entity.getSprite();
}
//
//
//
Vector3 Pitch::toScreenSpace(const Vector3& in_vector) const {
    return {in_vector.x + dimensions.origin.x, dimensions.origin.y + dimensions.bounds.getSize().y - in_vector.y};
}
//
//
//
Vector3 Pitch::toPitchSpace(const Vector3& in_vector) const {
    float origin = dimensions.origin.y;
    float height = dimensions.bounds.getSize().y;
    return {in_vector.x - dimensions.origin.x, origin + height - in_vector.y};
}
//
//
//
void Pitch::init_bounds() {
    dimensions.bounds.setFillColor(sf::Color::Transparent);
    dimensions.bounds.setOutlineColor(sf::ChalkWhite);
    dimensions.bounds.setOutlineThickness(BorderLineThickness);
    dimensions.bounds.setSize(sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                                           static_cast<float>(Metrics::MetersToPixels(105))));
    dimensions.bounds.setPosition(BorderLineThickness, BorderLineThickness);

    dimensions.draw_bounds_north.setFillColor(sf::Color::Transparent);
    dimensions.draw_bounds_north.setOutlineColor(sf::ChalkWhite);
    dimensions.draw_bounds_north.setOutlineThickness(BorderLineThickness);
    dimensions.draw_bounds_north.setSize(sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                                                      static_cast<float>(Metrics::MetersToPixels(105))));
    dimensions.draw_bounds_north.setPosition(BorderLineThickness, BorderLineThickness);
    dimensions.draw_bounds_north.setSize(
        {dimensions.draw_bounds_north.getSize().x, dimensions.draw_bounds_north.getSize().y / 2});

    dimensions.draw_bounds_south.setFillColor(sf::Color::Transparent);
    dimensions.draw_bounds_south.setOutlineColor(sf::ChalkWhite);
    dimensions.draw_bounds_south.setOutlineThickness(BorderLineThickness);
    dimensions.draw_bounds_south.setSize(sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                                                      static_cast<float>(Metrics::MetersToPixels(105))));
    dimensions.draw_bounds_south.setPosition(-BorderLineThickness, -BorderLineThickness);
    dimensions.draw_bounds_south.setSize(
        {dimensions.draw_bounds_south.getSize().x, dimensions.draw_bounds_south.getSize().y / 2});
}
//
//
//
void Pitch::init_6_yard_boxes() {
    float w = static_cast<float>(Metrics::MetersToPixels(18.32f));
    float h = static_cast<float>(Metrics::MetersToPixels(5.5f));
    dimensions.south_6.setSize(sf::Vector2f(w, h));
    dimensions.south_6.setFillColor(sf::Color::Transparent);
    dimensions.south_6.setOutlineColor(sf::ChalkWhite);
    dimensions.south_6.setOutlineThickness(StandardLineThickness);
    float x = (dimensions.bounds.getSize().x / 2) - (dimensions.south_6.getSize().x / 2);
    float y = dimensions.bounds.getSize().y - dimensions.south_6.getSize().y;
    dimensions.south_6.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_18_yard_boxes() {
    float w = static_cast<float>(Metrics::MetersToPixels(40.32f));
    float h = static_cast<float>(Metrics::MetersToPixels(16.5f));
    dimensions.south_18.setSize(sf::Vector2f(w, h));
    dimensions.south_18.setFillColor(sf::Color::Transparent);
    dimensions.south_18.setOutlineColor(sf::ChalkWhite);
    dimensions.south_18.setOutlineThickness(StandardLineThickness);
    float x = (dimensions.bounds.getSize().x / 2) - (dimensions.south_18.getSize().x / 2);
    float y = dimensions.bounds.getSize().y - dimensions.south_18.getSize().y;
    dimensions.south_18.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_center_circle() {
    dimensions.center_circle.setPointCount(60);
    dimensions.center_circle.setRadius(Metrics::MetersToPixels(9.15f));
    dimensions.center_circle.setFillColor(sf::Color::Transparent);
    dimensions.center_circle.setOutlineColor(sf::ChalkWhite);
    dimensions.center_circle.setOutlineThickness(StandardLineThickness);
    float x = (dimensions.bounds.getSize().x / 2) - dimensions.center_circle.getRadius();
    float y = (dimensions.bounds.getSize().y / 2) - dimensions.center_circle.getRadius();
    dimensions.center_circle.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_center_spot() {
    dimensions.center_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.center_spot.setFillColor(sf::ChalkWhite);
    float x = (dimensions.bounds.getSize().x / 2) - dimensions.center_spot.getRadius();
    float y = (dimensions.bounds.getSize().y / 2) - dimensions.center_spot.getRadius();
    dimensions.center_spot.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_penalty_spots() {
    dimensions.south_penalty_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.south_penalty_spot.setFillColor(sf::ChalkWhite);
    float x = dimensions.bounds.getSize().x / 2;
    float y = dimensions.bounds.getSize().y - Metrics::MetersToPixels(10.9f);
    dimensions.south_penalty_spot.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_north_arc() {
    dimensions.south_arc.setPointCount(60);
    dimensions.south_arc.setRadius(Metrics::MetersToPixels(7.f));
    dimensions.south_arc.setFillColor(sf::Color::Transparent);
    dimensions.south_arc.setOutlineColor(sf::ChalkWhite);
    dimensions.south_arc.setOutlineThickness(StandardLineThickness);
    dimensions.south_arc.setOrigin(sf::Vector2f(dimensions.south_arc.getRadius(), dimensions.south_arc.getRadius()));
    dimensions.south_arc.setRotation(-90);
    float x = dimensions.bounds.getSize().x / 2;
    float y = dimensions.bounds.getSize().y - dimensions.south_18.getSize().y - 2;
    dimensions.south_arc.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_halfway_line() {
    dimensions.halfway_line.setSize({dimensions.bounds.getSize().x, 2});
    dimensions.halfway_line.setFillColor(sf::ChalkWhite);
    float x = 0;
    float y = dimensions.bounds.getSize().y / 2;
    dimensions.halfway_line.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::update() {
    sprite.setPosition(movable.position.x, movable.position.y);
    minimap_entity.update();
}
