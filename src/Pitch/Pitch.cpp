#include "Pitch.hpp"

#include "Engine/Metrics.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace Engine;
//
//
//
Pitch::Pitch(SharedPtr<sf::Texture> in_texture, const sf::FloatRect in_world_bounds) {
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

    // 6 yard boxes
    init_6_yard_boxes();

    // 18 yard boxes
    init_18_yard_boxes();

    // center circle
    init_center_circle();

    // center spot
    init_center_spot();

    // pen spots
    init_penalty_spots();

    // north arc
    init_north_arc();

    // south arc
    init_south_arc();

    // halfway line
    init_halfway_line();
}
//
//
//
void Pitch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    pitch_texture->clear();
    pitch_texture->draw(grass);
    pitch_texture->draw(dimensions.bounds);
    pitch_texture->draw(dimensions.north_6);
    pitch_texture->draw(dimensions.south_6);
    pitch_texture->draw(dimensions.north_18);
    pitch_texture->draw(dimensions.south_18);
    pitch_texture->draw(dimensions.center_circle);
    pitch_texture->draw(dimensions.center_spot);
    pitch_texture->draw(dimensions.north_penalty_spot);
    pitch_texture->draw(dimensions.north_arc);
    pitch_texture->draw(dimensions.south_arc);
    pitch_texture->draw(dimensions.halfway_line);
    pitch_texture->display();
    target.draw(pitch);
}
//
//
//
void Pitch::init_bounds() {
    dimensions.bounds.setPosition(200, 200);
    dimensions.bounds.setSize(sf::Vector2f(static_cast<float>(Metrics::MetersToPixels(69)),
                                           static_cast<float>(Metrics::MetersToPixels(105))));
    dimensions.bounds.setFillColor(sf::Color::Transparent);
    dimensions.bounds.setOutlineColor(sf::ChalkWhite);
    dimensions.bounds.setOutlineThickness(2);
}
//
//
//
void Pitch::init_6_yard_boxes() {
    float x, y, w, h;

    w = static_cast<float>(Metrics::MetersToPixels(18.32f));
    h = static_cast<float>(Metrics::MetersToPixels(5.5f));
    dimensions.north_6.setSize(sf::Vector2f(w, h));

    x = (dimensions.bounds.getPosition().x + (dimensions.bounds.getSize().x / 2)) -
        (dimensions.north_6.getSize().x / 2);

    y = dimensions.bounds.getPosition().y;

    dimensions.north_6.setPosition(sf::Vector2f(x, y));
    dimensions.north_6.setFillColor(sf::Color::Transparent);
    dimensions.north_6.setOutlineColor(sf::ChalkWhite);
    dimensions.north_6.setOutlineThickness(2);

    // south
    dimensions.south_6 = dimensions.north_6;
    dimensions.south_6.setPosition(
        dimensions.north_6.getPosition().x,
        dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y - dimensions.south_6.getSize().y);
    dimensions.south_6.setFillColor(sf::Color::Transparent);
    dimensions.south_6.setOutlineColor(sf::ChalkWhite);
    dimensions.south_6.setOutlineThickness(2);
}
//
//
//
void Pitch::init_18_yard_boxes() {
    // north
    float x, y, w, h;

    w = static_cast<float>(Metrics::MetersToPixels(40.32f));
    h = static_cast<float>(Metrics::MetersToPixels(16.5f));
    dimensions.north_18.setSize(sf::Vector2f(w, h));

    x = (dimensions.bounds.getPosition().x + (dimensions.bounds.getSize().x / 2)) -
        (dimensions.north_18.getSize().x / 2);

    y = dimensions.bounds.getPosition().y;

    dimensions.north_18.setPosition(sf::Vector2f(x, y));
    dimensions.north_18.setFillColor(sf::Color::Transparent);
    dimensions.north_18.setOutlineColor(sf::ChalkWhite);
    dimensions.north_18.setOutlineThickness(2);

    // south
    dimensions.south_18 = dimensions.north_18;
    dimensions.south_18.setPosition(
        dimensions.north_18.getPosition().x,
        dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y - dimensions.south_18.getSize().y);

    dimensions.south_18.setFillColor(sf::Color::Transparent);
    dimensions.south_18.setOutlineColor(sf::ChalkWhite);
    dimensions.south_18.setOutlineThickness(2);
}
//
//
//
void Pitch::init_center_circle() {
    dimensions.center_circle.setPointCount(60);
    dimensions.center_circle.setRadius(Metrics::MetersToPixels(9.15f));
    dimensions.center_circle.setPosition(
        dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2 - dimensions.center_circle.getRadius(),
        dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2 - dimensions.center_circle.getRadius());
    dimensions.center_circle.setFillColor(sf::Color::Transparent);
    dimensions.center_circle.setOutlineColor(sf::ChalkWhite);
    dimensions.center_circle.setOutlineThickness(2);
}
//
//
//
void Pitch::init_center_spot() {
    int x, y;
    x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;

    y = dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2 - 2;

    dimensions.center_spot.setPosition(x, y);
    dimensions.center_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.center_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void Pitch::init_penalty_spots() {
    // north
    int x, y;
    x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
    y = dimensions.bounds.getPosition().y + Metrics::MetersToPixels(10.9f);

    dimensions.north_penalty_spot.setPosition(x, y);
    dimensions.north_penalty_spot.setRadius(Metrics::MetersToPixels(0.2f));
    dimensions.north_penalty_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void Pitch::init_north_arc() {
    dimensions.north_arc.setPointCount(60);
    int x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
    int y = dimensions.bounds.getPosition().y + dimensions.north_18.getSize().y + 2;

    dimensions.north_arc.setPosition(x, y);
    dimensions.north_arc.setRadius(Metrics::MetersToPixels(7.f));

    dimensions.north_arc.setFillColor(sf::Color::Transparent);
    dimensions.north_arc.setOutlineColor(sf::ChalkWhite);
    dimensions.north_arc.setOutlineThickness(2);
    dimensions.north_arc.setOrigin(sf::Vector2f(dimensions.north_arc.getRadius(), dimensions.north_arc.getRadius()));
    dimensions.north_arc.setRotation(90);
}
//
//
//
void Pitch::init_south_arc() {
    dimensions.south_arc.setPointCount(60);
    int x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
    int y = dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y - dimensions.south_18.getSize().y - 2;

    dimensions.south_arc.setPosition(x, y);
    dimensions.south_arc.setRadius(Metrics::MetersToPixels(7.f));

    dimensions.south_arc.setFillColor(sf::Color::Transparent);
    dimensions.south_arc.setOutlineColor(sf::ChalkWhite);
    dimensions.south_arc.setOutlineThickness(2);
    dimensions.south_arc.setOrigin(sf::Vector2f(dimensions.south_arc.getRadius(), dimensions.south_arc.getRadius()));
    dimensions.south_arc.setRotation(-90);
}
//
//
//
void Pitch::init_halfway_line() {
    dimensions.halfway_line.setSize({dimensions.bounds.getSize().x, 2});

    dimensions.halfway_line.setPosition(dimensions.bounds.getPosition().x,
                                        dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2);
    dimensions.halfway_line.setFillColor(sf::ChalkWhite);
}
//
//
//
float Pitch::mirrorX(const float in_x) const {
    float out_x = 0;
    float middle = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
    float dist_from_middle = fabs(in_x - middle);
    if (in_x < middle) {
        out_x = in_x + dist_from_middle * 2;
    } else {
        out_x = in_x - dist_from_middle * 2;
    }

    return out_x;
}
//
//
//
float Pitch::mirrorY(const float in_y) const {
    float out_y = 0;
    float middle = dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2;
    float dist_from_middle = fabs(in_y - middle);
    if (in_y < middle) {
        out_y = in_y + dist_from_middle * 2;
    } else {
        out_y = in_y - dist_from_middle * 2;
    }

    return out_y;
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
