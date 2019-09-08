#include "grass.hpp"
//
//
//
void make_grass_sprite(int sprite, const std::string &spritesheet) {
  //  sf::Texture *tex = acquire_texture(spritesheet);
  //  tex->setRepeated(true);
  //  sprite_pool[sprite].setTexture(*tex);
  //  set_sprite_z(sprite_pool[sprite], -1);
}
//
//
//
void init_grass(Grass &grass, const std::string &spritesheet, Camera &camera) {
  //  int e = acquire_entity();
  //  entity_pool[e].type = EntityType::Background;
  //  grass.entity = e;
  //  entity_pool[e].sprite = acquire_sprite(&entity_pool[e]);
  //  GrassSprite.spritesheet = spritesheet;
  //  make_grass_sprite(entity_pool[e].sprite, GrassSprite.spritesheet);
  //  update_grass(grass, camera);
}
//
//
//
void update_grass(Grass &grass, Camera &camera) {
  static const int SAFETY_OFFSET = 20;
  sf::IntRect rect;
  rect.width = camera.view.getSize().x + SAFETY_OFFSET * 4;
  rect.height = camera.view.getSize().y + SAFETY_OFFSET * 4;
  rect.left = camera.view.getCenter().x - rect.width / 2 - SAFETY_OFFSET;
  rect.top = camera.view.getCenter().y - rect.height / 2 - SAFETY_OFFSET;
  GrassSprite.setPosition(rect.left, rect.top);
  GrassSprite.setTextureRect(rect);
}
