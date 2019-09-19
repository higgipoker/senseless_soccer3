#include "Pitch.hpp"

#include "Engine/Metrics.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
//
//
//
Pitch::Pitch(std::shared_ptr<sf::Texture> in_texture,
             const sf::IntRect in_world_bounds) {
  // set up the repeating grass texture
  in_texture->setRepeated(true);
  grass.setTexture(*in_texture);

  // make a texture for drawing the lines on
  pitch_texture = new sf::RenderTexture();
  pitch_texture->create(
      static_cast<float>(Engine::Metrics::MetersToPixels(69) + 400),
      static_cast<float>(Engine::Metrics::MetersToPixels(105) + 400));
  pitch.setTexture(pitch_texture->getTexture());

  // size of the target rect for grass tile
  grass.setTextureRect(
      sf::IntRect{0, 0, static_cast<int>(pitch_texture->getSize().x),
                  static_cast<int>(pitch_texture->getSize().y)});

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
Pitch::~Pitch() { delete pitch_texture; }
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
  dimensions.bounds.setSize(
      sf::Vector2f(static_cast<float>(Engine::Metrics::MetersToPixels(69)),
                   static_cast<float>(Engine::Metrics::MetersToPixels(105))));
  dimensions.bounds.setFillColor(sf::Color::Transparent);
  dimensions.bounds.setOutlineColor(sf::ChalkWhite);
  dimensions.bounds.setOutlineThickness(2);
}
//
//
//
void Pitch::init_6_yard_boxes() {
  float x, y, w, h;

  w = static_cast<float>(Engine::Metrics::MetersToPixels(18.32f));
  h = static_cast<float>(Engine::Metrics::MetersToPixels(5.5f));
  dimensions.north_6.setSize(sf::Vector2f(w, h));

  x = (dimensions.bounds.getPosition().x +
       (dimensions.bounds.getSize().x / 2)) -
      (dimensions.north_6.getSize().x / 2);

  y = dimensions.bounds.getPosition().y;

  dimensions.north_6.setPosition(sf::Vector2f(x, y));
  dimensions.north_6.setFillColor(sf::Color::Transparent);
  dimensions.north_6.setOutlineColor(sf::ChalkWhite);
  dimensions.north_6.setOutlineThickness(2);

  // south
  dimensions.south_6 = dimensions.north_6;
  dimensions.south_6.setPosition(dimensions.north_6.getPosition().x,
                                 dimensions.bounds.getPosition().y +
                                     dimensions.bounds.getSize().y -
                                     dimensions.south_6.getSize().y);
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

  w = static_cast<float>(Engine::Metrics::MetersToPixels(40.32f));
  h = static_cast<float>(Engine::Metrics::MetersToPixels(16.5f));
  dimensions.north_18.setSize(sf::Vector2f(w, h));

  x = (dimensions.bounds.getPosition().x +
       (dimensions.bounds.getSize().x / 2)) -
      (dimensions.north_18.getSize().x / 2);

  y = dimensions.bounds.getPosition().y;

  dimensions.north_18.setPosition(sf::Vector2f(x, y));
  dimensions.north_18.setFillColor(sf::Color::Transparent);
  dimensions.north_18.setOutlineColor(sf::ChalkWhite);
  dimensions.north_18.setOutlineThickness(2);

  // south
  dimensions.south_18 = dimensions.north_18;
  dimensions.south_18.setPosition(dimensions.north_18.getPosition().x,
                                  dimensions.bounds.getPosition().y +
                                      dimensions.bounds.getSize().y -
                                      dimensions.south_18.getSize().y);

  dimensions.south_18.setFillColor(sf::Color::Transparent);
  dimensions.south_18.setOutlineColor(sf::ChalkWhite);
  dimensions.south_18.setOutlineThickness(2);
}
//
//
//
void Pitch::init_center_circle() {
  dimensions.center_circle.setRadius(Engine::Metrics::MetersToPixels(9.15f));
  dimensions.center_circle.setPosition(
      dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2 -
          dimensions.center_circle.getRadius(),
      dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2 -
          dimensions.center_circle.getRadius());
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
  dimensions.center_spot.setRadius(Engine::Metrics::MetersToPixels(0.2f));
  dimensions.center_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void Pitch::init_penalty_spots() {
  // north
  int x, y;
  x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
  y = dimensions.bounds.getPosition().y +
      Engine::Metrics::MetersToPixels(10.9f);

  dimensions.north_penalty_spot.setPosition(x, y);
  dimensions.north_penalty_spot.setRadius(
      Engine::Metrics::MetersToPixels(0.2f));
  dimensions.north_penalty_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void Pitch::init_north_arc() {
  int x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
  int y =
      dimensions.bounds.getPosition().y + dimensions.north_18.getSize().y + 2;

  dimensions.north_arc.setPosition(x, y);
  dimensions.north_arc.setRadius(Engine::Metrics::MetersToPixels(7.f));

  dimensions.north_arc.setFillColor(sf::Color::Transparent);
  dimensions.north_arc.setOutlineColor(sf::ChalkWhite);
  dimensions.north_arc.setOutlineThickness(2);
  dimensions.north_arc.setOrigin(sf::Vector2f(
      dimensions.north_arc.getRadius(), dimensions.north_arc.getRadius()));
  dimensions.north_arc.setRotation(90);
}
//
//
//
void Pitch::init_south_arc() {
  int x = dimensions.bounds.getPosition().x + dimensions.bounds.getSize().x / 2;
  int y = dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y -
          dimensions.south_18.getSize().y - 2;

  dimensions.south_arc.setPosition(x, y);
  dimensions.south_arc.setRadius(Engine::Metrics::MetersToPixels(7.f));

  dimensions.south_arc.setFillColor(sf::Color::Transparent);
  dimensions.south_arc.setOutlineColor(sf::ChalkWhite);
  dimensions.south_arc.setOutlineThickness(2);
  dimensions.south_arc.setOrigin(sf::Vector2f(
      dimensions.south_arc.getRadius(), dimensions.south_arc.getRadius()));
  dimensions.south_arc.setRotation(-90);
}
//
//
//
void Pitch::init_halfway_line() {
  dimensions.halfway_line.setSize(
      sf::Vector2f(dimensions.bounds.getSize().x, 2));

  dimensions.halfway_line.setPosition(
      dimensions.bounds.getPosition().x,
      dimensions.bounds.getPosition().y + dimensions.bounds.getSize().y / 2);
  dimensions.halfway_line.setFillColor(sf::ChalkWhite);
}
