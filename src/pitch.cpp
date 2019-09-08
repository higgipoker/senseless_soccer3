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
  pitch.tex.create(static_cast<float>(MetersToPixels(69)),
                   static_cast<float>(MetersToPixels(105)));

  // set up the sprite to use the custom texture
  sprite_pool[entity_pool[pitch.entity].sprite].setTexture(
      pitch.tex.getTexture());

  // set up a default pitch size
  pitch.dimensions.bounds.setPosition(200, 200);
  pitch.dimensions.bounds.setSize(
      sf::Vector2f(static_cast<float>(MetersToPixels(69)),
                   static_cast<float>(MetersToPixels(105))));
  pitch.dimensions.bounds.setFillColor(sf::Color(0, 0, 0, 0));
  pitch.dimensions.bounds.setOutlineColor(sf::Color::White);
  pitch.dimensions.bounds.setOutlineThickness(2);
  pitch.dimensions.center_circle_radius = MetersToPixels(9.15f);
}
//
//
//
void update_pitch(Pitch &pitch, Camera &camera) {
  // updated grass texture depending on camera
  // update_grass(pitch.grass, camera);

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
  pitch.tex.display();
}
