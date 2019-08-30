#include "grass.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Sprite &get_sprite(Grass &grass) {
  return sprite_pool[entity_pool[grass.entity].sprite];
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Entity &get_ball_entity(Grass &grass) { return entity_pool[grass.entity]; }

// -----------------------------------------------------------------------------
// make_grass_sprite
// -----------------------------------------------------------------------------
void make_grass_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = acquire_texture(spritesheet);
  tex->setRepeated(true);
  sprite_pool[sprite].setTexture(*tex);
  set_sprite_z(sprite_pool[sprite], 0);
}

// -----------------------------------------------------------------------------
// init_grass
// -----------------------------------------------------------------------------
void init_grass(Grass &grass, Camera &camera) {
  int e = acquire_entity();
  entity_pool[e].type = EntityType::Background;
  grass.entity = e;
  grass.spritesheet = grass_tile;
  entity_pool[e].sprite = acquire_sprite(&entity_pool[e]);
  make_grass_sprite(entity_pool[e].sprite, grass.spritesheet);
  update_grass(grass, camera);
}
// -----------------------------------------------------------------------------
// update_grass
// -----------------------------------------------------------------------------
void update_grass(Grass &grass, Camera &camera) {
  static const int SAFETY_OFFSET = 20;
  sf::IntRect rect;
  rect.width = camera.view.getSize().x + SAFETY_OFFSET * 4;
  rect.height = camera.view.getSize().y + SAFETY_OFFSET * 4;
  rect.left = camera.view.getCenter().x - rect.width / 2 - SAFETY_OFFSET;
  rect.top = camera.view.getCenter().y - rect.height / 2 - SAFETY_OFFSET;
  get_sprite(grass).setPosition(rect.left, rect.top);
  get_sprite(grass).setTextureRect(rect);
}
