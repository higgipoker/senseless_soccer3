#include "Pitch.hpp"

#include "Engine/Metrics.hpp"
#include "Engine/Texture.hpp"

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
Pitch::Pitch(const std::string& in_grass_texture, const sf::FloatRect in_world_bounds) {
    // tmp test
    dimensions.origin = {200, 200};
    // set up the repeating grass texture
    Texture tex_grass;
    tex_grass.loadFromFile(in_grass_texture);
    sf::Sprite grass;
    tex_grass.setRepeated(true);
    grass.setTexture(tex_grass);

    // make a texture for drawing the lines on
    pitch_texture.create(in_world_bounds.width, in_world_bounds.height);
    pitch.setTexture(pitch_texture.getTexture());

    // size of the target rect for grass tile
    grass.setTextureRect(
        sf::IntRect{0, 0, static_cast<int>(pitch_texture.getSize().x), static_cast<int>(pitch_texture.getSize().y)});

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
    translate.translate({dimensions.origin.toSfVector()});
    flip.rotate(180, {dimensions.bounds.getSize().x / 2, dimensions.bounds.getSize().y / 2});
    translate_and_flip.translate({dimensions.origin.toSfVector()});
    translate_and_flip.rotate(180, {dimensions.bounds.getSize().x / 2, dimensions.bounds.getSize().y / 2});

    // draw grass and lines to the texture
    pitch_texture.clear();
    pitch_texture.draw(grass);
    pitch_texture.draw(dimensions.draw_bounds, translate);
    pitch_texture.draw(dimensions.draw_bounds, translate_and_flip);
    pitch_texture.draw(dimensions.south_6, translate);
    pitch_texture.draw(dimensions.south_6, translate_and_flip);
    pitch_texture.draw(dimensions.south_18, translate);
    pitch_texture.draw(dimensions.south_18, translate_and_flip);
    pitch_texture.draw(dimensions.center_circle, translate);
    pitch_texture.draw(dimensions.center_spot, translate);
    pitch_texture.draw(dimensions.south_penalty_spot, translate);
    pitch_texture.draw(dimensions.south_penalty_spot, translate_and_flip);
    pitch_texture.draw(dimensions.south_arc, translate);
    pitch_texture.draw(dimensions.south_arc, translate_and_flip);
    //    pitch_texture.draw(dimensions.halfway_line, translate);
    pitch_texture.display();
}
//
//
//
void Pitch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(pitch);
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
    dimensions.bounds.setPosition(0, 0);
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
    dimensions.south_6.setSize(sf::Vector2f(w, h));
    dimensions.south_6.setFillColor(sf::Color::Transparent);
    dimensions.south_6.setOutlineColor(sf::ChalkWhite);
    dimensions.south_6.setOutlineThickness(StandardLineThickness);

    float x = (dimensions.bounds.getSize().x / 2) - (dimensions.south_6.getSize().x / 2);
    float y = dimensions.bounds.getSize().y - dimensions.south_6.getSize().y;

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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
    float y = dimensions.south_18.getSize().y - dimensions.south_18.getSize().y;

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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

    //    Vector3 tmp = toScreenSpace({x, y});
    //    x = tmp.x, y = tmp.y;
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
    //  float desired_width = pitch_texture.getSize().x /(1-dist_from_camera);
    //  float desired_height = pitch_texture.getSize().y /(1-dist_from_camera);
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
