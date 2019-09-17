#include "pitch.hpp"

#include "metrics.hpp"
///
///
///
void init_pitch(Pitch &pitch, const std::string &grass_spritesheet,
                Camera &camera) {
  // the scrolling grass texture
  // init_grass(pitch.grass, grass_spritesheet, camera);
  sf::Texture *tex = acquire_texture(grass_spritesheet);
  tex->setRepeated(true);
  pitch.grass.setTexture(*tex);

  // entity
  pitch.entity = acquire_entity();
  entity_pool[pitch.entity].sprite = acquire_sprite(&entity_pool[pitch.entity]);

  // make a texture for drawing the lines on
  pitch.tex.create(static_cast<float>(MetersToPixels(69) + 400),
                   static_cast<float>(MetersToPixels(105) + 400));

  // set up the sprite to use the custom texture
  sprite_pool[entity_pool[pitch.entity].sprite].setTexture(
      pitch.tex.getTexture());

  set_sprite_z(sprite_pool[entity_pool[pitch.entity].sprite], -1);

  // pitch bounds
  init_bounds(pitch);

  // 6 yard boxes
  init_6_yard_boxes(pitch);

  // 18 yard boxes
  init_18_yard_boxes(pitch);

  // center circle
  init_center_circle(pitch);

  // center spot
  init_center_spot(pitch);

  // pen spots
  init_penalty_spots(pitch);

  // north arc
  init_north_arc(pitch);

  // south arc
  init_south_arc(pitch);

  // halfway line
  init_halfway_line(pitch);
}
//
//
//
void init_bounds(Pitch &pitch) {
  pitch.dimensions.bounds.setPosition(200, 200);
  pitch.dimensions.bounds.setSize(
      sf::Vector2f(static_cast<float>(MetersToPixels(69)),
                   static_cast<float>(MetersToPixels(105))));
  pitch.dimensions.bounds.setFillColor(sf::Color::Transparent);
  pitch.dimensions.bounds.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.bounds.setOutlineThickness(2);
}
//
//
//
void init_6_yard_boxes(Pitch &pitch) {
  float x, y, w, h;

  w = static_cast<float>(MetersToPixels(18.32f));
  h = static_cast<float>(MetersToPixels(5.5f));
  pitch.dimensions.north_6.setSize(sf::Vector2f(w, h));

  x = (pitch.dimensions.bounds.getPosition().x +
       (pitch.dimensions.bounds.getSize().x / 2)) -
      (pitch.dimensions.north_6.getSize().x / 2);

  y = pitch.dimensions.bounds.getPosition().y;

  pitch.dimensions.north_6.setPosition(sf::Vector2f(x, y));
  pitch.dimensions.north_6.setFillColor(sf::Color::Transparent);
  pitch.dimensions.north_6.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.north_6.setOutlineThickness(2);

  // south
  pitch.dimensions.south_6 = pitch.dimensions.north_6;
  pitch.dimensions.south_6.setPosition(
      pitch.dimensions.north_6.getPosition().x,
      pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.bounds.getSize().y -
          pitch.dimensions.south_6.getSize().y);
  pitch.dimensions.south_6.setFillColor(sf::Color::Transparent);
  pitch.dimensions.south_6.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.south_6.setOutlineThickness(2);
}
//
//
//
void init_18_yard_boxes(Pitch &pitch) {
  // north
  float x, y, w, h;

  w = static_cast<float>(MetersToPixels(40.32f));
  h = static_cast<float>(MetersToPixels(16.5f));
  pitch.dimensions.north_18.setSize(sf::Vector2f(w, h));

  x = (pitch.dimensions.bounds.getPosition().x +
       (pitch.dimensions.bounds.getSize().x / 2)) -
      (pitch.dimensions.north_18.getSize().x / 2);

  y = pitch.dimensions.bounds.getPosition().y;

  pitch.dimensions.north_18.setPosition(sf::Vector2f(x, y));
  pitch.dimensions.north_18.setFillColor(sf::Color::Transparent);
  pitch.dimensions.north_18.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.north_18.setOutlineThickness(2);

  // south
  pitch.dimensions.south_18 = pitch.dimensions.north_18;
  pitch.dimensions.south_18.setPosition(
      pitch.dimensions.north_18.getPosition().x,
      pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.bounds.getSize().y -
          pitch.dimensions.south_18.getSize().y);

  pitch.dimensions.south_18.setFillColor(sf::Color::Transparent);
  pitch.dimensions.south_18.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.south_18.setOutlineThickness(2);
}
//
//
//
void init_center_circle(Pitch &pitch) {
  pitch.dimensions.center_circle.setRadius(MetersToPixels(9.15f));
  pitch.dimensions.center_circle.setPosition(
      pitch.dimensions.bounds.getPosition().x +
          pitch.dimensions.bounds.getSize().x / 2 -
          pitch.dimensions.center_circle.getRadius(),
      pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.bounds.getSize().y / 2 -
          pitch.dimensions.center_circle.getRadius());
  pitch.dimensions.center_circle.setFillColor(sf::Color::Transparent);
  pitch.dimensions.center_circle.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.center_circle.setOutlineThickness(2);
}
//
//
//
void init_center_spot(Pitch &pitch) {
  int x, y;
  x = pitch.dimensions.bounds.getPosition().x +
      pitch.dimensions.bounds.getSize().x / 2;

  y = pitch.dimensions.bounds.getPosition().y +
      pitch.dimensions.bounds.getSize().y / 2 - 2;

  pitch.dimensions.center_spot.setPosition(x, y);
  pitch.dimensions.center_spot.setRadius(MetersToPixels(0.2f));
  pitch.dimensions.center_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void init_penalty_spots(Pitch &pitch) {
  // north
  int x, y, w, h;
  x = pitch.dimensions.bounds.getPosition().x +
      pitch.dimensions.bounds.getSize().x / 2;
  y = pitch.dimensions.bounds.getPosition().y + MetersToPixels(10.9f);

  pitch.dimensions.north_penalty_spot.setPosition(x, y);
  pitch.dimensions.north_penalty_spot.setRadius(MetersToPixels(0.2f));
  pitch.dimensions.north_penalty_spot.setFillColor(sf::ChalkWhite);
}
//
//
//
void init_north_arc(Pitch &pitch) {
  int x = pitch.dimensions.bounds.getPosition().x +
          pitch.dimensions.bounds.getSize().x / 2;
  int y = pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.north_18.getSize().y + 2;

  pitch.dimensions.north_arc.setPosition(x, y);
  pitch.dimensions.north_arc.setRadius(MetersToPixels(7.f));

  pitch.dimensions.north_arc.setFillColor(sf::Color::Transparent);
  pitch.dimensions.north_arc.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.north_arc.setOutlineThickness(2);
  pitch.dimensions.north_arc.setOrigin(
      sf::Vector2f(pitch.dimensions.north_arc.getRadius(),
                   pitch.dimensions.north_arc.getRadius()));
  pitch.dimensions.north_arc.setRotation(90);
}
//
//
//
void init_south_arc(Pitch &pitch) {
  int x = pitch.dimensions.bounds.getPosition().x +
          pitch.dimensions.bounds.getSize().x / 2;
  int y = pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.bounds.getSize().y -
          pitch.dimensions.south_18.getSize().y - 2;

  pitch.dimensions.south_arc.setPosition(x, y);
  pitch.dimensions.south_arc.setRadius(MetersToPixels(7.f));

  pitch.dimensions.south_arc.setFillColor(sf::Color::Transparent);
  pitch.dimensions.south_arc.setOutlineColor(sf::ChalkWhite);
  pitch.dimensions.south_arc.setOutlineThickness(2);
  pitch.dimensions.south_arc.setOrigin(
      sf::Vector2f(pitch.dimensions.south_arc.getRadius(),
                   pitch.dimensions.south_arc.getRadius()));
  pitch.dimensions.south_arc.setRotation(-90);
}
//
//
//
void init_halfway_line(Pitch &pitch) {
  pitch.dimensions.halfway_line.setSize(
      sf::Vector2f(pitch.dimensions.bounds.getSize().x, 2));

  pitch.dimensions.halfway_line.setPosition(
      pitch.dimensions.bounds.getPosition().x,
      pitch.dimensions.bounds.getPosition().y +
          pitch.dimensions.bounds.getSize().y / 2);
  pitch.dimensions.halfway_line.setFillColor(sf::ChalkWhite);
}
//
//
//
void update_pitch(Pitch &pitch, Camera &camera) {
  // uodate the grass tile
  static const int SAFETY_OFFSET = 20;
  sf::IntRect rect;
  rect.width = camera.view.getSize().x + SAFETY_OFFSET * 4;
  rect.height = camera.view.getSize().y + SAFETY_OFFSET * 4;
  rect.left = camera.view.getCenter().x - rect.width / 2 - SAFETY_OFFSET;
  rect.top = camera.view.getCenter().y - rect.height / 2 - SAFETY_OFFSET;
  pitch.grass.setPosition(rect.left, rect.top);
  pitch.grass.setTextureRect(rect);

  // update the main texture
  pitch.tex.clear();
  pitch.tex.draw(pitch.grass);
  pitch.tex.draw(pitch.dimensions.bounds);
  pitch.tex.draw(pitch.dimensions.north_6);
  pitch.tex.draw(pitch.dimensions.south_6);
  pitch.tex.draw(pitch.dimensions.north_18);
  pitch.tex.draw(pitch.dimensions.south_18);
  pitch.tex.draw(pitch.dimensions.center_circle);
  pitch.tex.draw(pitch.dimensions.center_spot);
  pitch.tex.draw(pitch.dimensions.north_penalty_spot);
  pitch.tex.draw(pitch.dimensions.north_arc);
  pitch.tex.draw(pitch.dimensions.south_arc);
  pitch.tex.draw(pitch.dimensions.halfway_line);
  pitch.tex.display();
}
