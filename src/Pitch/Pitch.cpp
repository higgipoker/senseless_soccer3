#include "Pitch.hpp"

#include "Engine/Metrics.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
//
//
//
namespace sf {
inline Color ChalkWhite{210, 210, 210, 255};
}
//
const int StandardLineThickness = 2;

using namespace Engine;
//
//
//
Pitch::Pitch(SharedPtr<sf::Texture> in_texture, const sf::FloatRect in_world_bounds) {
    // tmp test
    dimensions.origin = {200, 200};
    // set up the repeating grass texture
    in_texture->setRepeated(true);
    grass.setTexture(*in_texture);

    // make a texture for drawing the lines on
    pitch_texture->create(in_world_bounds.width, in_world_bounds.height);
    pitch.setTexture(pitch_texture->getTexture());

    // size of the target rect for grass tile
    grass.setTextureRect(
        sf::IntRect{0, 0, static_cast<int>(pitch_texture->getSize().x), static_cast<int>(pitch_texture->getSize().y)});

    // abs width of texture when at default distance from camera
    perspective_width = in_world_bounds.width;

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

    // flips
    flip.rotate(180, dimensions.center_spot.getCenter());
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
void Pitch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    pitch_texture->clear();
    pitch_texture->draw(grass);
    pitch_texture->draw(dimensions.draw_bounds);
    pitch_texture->draw(dimensions.draw_bounds, flip);
    pitch_texture->draw(dimensions.north_6);
    pitch_texture->draw(dimensions.north_6, flip);
    pitch_texture->draw(dimensions.north_18);
    pitch_texture->draw(dimensions.north_18, flip);
    pitch_texture->draw(dimensions.center_circle);
    pitch_texture->draw(dimensions.center_spot);
    pitch_texture->draw(dimensions.north_penalty_spot);
    pitch_texture->draw(dimensions.north_penalty_spot, flip);
    pitch_texture->draw(dimensions.north_arc);
    pitch_texture->draw(dimensions.north_arc, flip);
    pitch_texture->draw(dimensions.halfway_line);
    pitch_texture->display();
    target.draw(pitch);
}
//
//
//
void Pitch::init_bounds() {
    dimensions.bounds.setPosition({dimensions.origin.toSfVector()});
    dimensions.bounds.setSize(sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                                           static_cast<float>(Metrics::MetersToPixels(105))));
    dimensions.bounds.setFillColor(sf::Color::Transparent);
    dimensions.bounds.setOutlineColor(sf::ChalkWhite);
    dimensions.bounds.setOutlineThickness(2);

    dimensions.draw_bounds = dimensions.bounds;
    dimensions.draw_bounds.setSize({dimensions.bounds.getSize().x, dimensions.bounds.getSize().y / 2});
}
//
//
//
void Pitch::init_6_yard_boxes() {
    float w = static_cast<float>(Metrics::MetersToPixels(18.32f));
    float h = static_cast<float>(Metrics::MetersToPixels(5.5f));
    dimensions.north_6.setSize(sf::Vector2f(w, h));
    dimensions.north_6.setFillColor(sf::Color::Transparent);
    dimensions.north_6.setOutlineColor(sf::ChalkWhite);
    dimensions.north_6.setOutlineThickness(StandardLineThickness);

    float x = (dimensions.bounds.getSize().x / 2) - (dimensions.north_6.getSize().x / 2);
    float y = dimensions.bounds.getSize().y;

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.north_6.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_18_yard_boxes() {
    float w = static_cast<float>(Metrics::MetersToPixels(40.32f));
    float h = static_cast<float>(Metrics::MetersToPixels(16.5f));
    dimensions.north_18.setSize(sf::Vector2f(w, h));
    dimensions.north_18.setFillColor(sf::Color::Transparent);
    dimensions.north_18.setOutlineColor(sf::ChalkWhite);
    dimensions.north_18.setOutlineThickness(StandardLineThickness);

    float x = (dimensions.bounds.getSize().x / 2) - (dimensions.north_18.getSize().x / 2);
    float y = dimensions.north_18.getSize().y;

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.north_18.setPosition(sf::Vector2f(x, y));
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
    float y = (dimensions.bounds.getSize().y / 2) + dimensions.center_circle.getRadius();

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.center_circle.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_center_spot() {
    dimensions.center_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.center_spot.setFillColor(sf::ChalkWhite);

    float x = (dimensions.bounds.getSize().x / 2) - dimensions.center_spot.getRadius();
    float y = (dimensions.bounds.getSize().y / 2) + dimensions.center_spot.getRadius();

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.center_spot.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_penalty_spots() {
    dimensions.north_penalty_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.north_penalty_spot.setFillColor(sf::ChalkWhite);

    float x = dimensions.bounds.getSize().x / 2;
    float y = dimensions.bounds.getSize().y - Metrics::MetersToPixels(10.9f);

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.north_penalty_spot.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_north_arc() {
    dimensions.north_arc.setPointCount(60);
    dimensions.north_arc.setRadius(Metrics::MetersToPixels(7.f));
    dimensions.north_arc.setFillColor(sf::Color::Transparent);
    dimensions.north_arc.setOutlineColor(sf::ChalkWhite);
    dimensions.north_arc.setOutlineThickness(StandardLineThickness);
    dimensions.north_arc.setOrigin(sf::Vector2f(dimensions.north_arc.getRadius(), dimensions.north_arc.getRadius()));
    dimensions.north_arc.setRotation(90);

    float x = dimensions.bounds.getSize().x / 2;
    float y = dimensions.bounds.getSize().y - dimensions.north_18.getSize().y - 2;

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.north_arc.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::init_halfway_line() {
    dimensions.halfway_line.setSize({dimensions.bounds.getSize().x, 2});
    dimensions.halfway_line.setFillColor(sf::ChalkWhite);

    float x = 0;
    float y = dimensions.bounds.getSize().y / 2;

    Vector3 tmp = toScreenSpace({x, y});
    x = tmp.x, y = tmp.y;
    dimensions.halfway_line.setPosition(sf::Vector2f(x, y));
}
//
//
//
void Pitch::perspectivize(const float in_camera_height) {
    //  float dist_from_camera = in_camera_height - entity_height - 50;
    //  dist_from_camera = -dist_from_camera;
    //  if(dist_from_camera){
    //  float desired_width = pitch_texture->getSize().x /(1-dist_from_camera);
    //  float desired_height = pitch_texture->getSize().y /(1-dist_from_camera);
    //  float scale_factor_x = desired_width / pitch.getLocalBounds().width;
    //  float scale_factor_y = desired_height / pitch.getLocalBounds().height;
    //  pitch.setScale(scale_factor_x, scale_factor_y);
    //  }
    if (perspectivizable) {
        // size depending on distance from camera
        //    float dimensions = perspective_width;
        //    float dist_from_camera = in_camera_height - entity_height;

        //    // other side of camera, don't perspectivize!
        //    if (dist_from_camera <= 0) {
        //      setScale({0.f, 0.f});
        //      return;
        //    }

        //    float angular_diameter = 2 * (atanf(dimensions / (2 *
        //    dist_from_camera))); float degs = Degrees(angular_diameter); float
        //    sprite_scale_factor = degs / dimensions; float sprite_ratio =
        //    dimensions / getLocalBounds().width; sprite_scale_factor *=
        //    sprite_ratio; pitch.setScale(sprite_scale_factor,
        //    sprite_scale_factor);
    }
}
