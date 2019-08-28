#include "camera.hpp"
#include "physics.hpp"

#include "data.hpp"
#include "entity.hpp"

void init_camera(Camera &camera, Game &game) {
  int e = acquire_entity();
  camera.entity = &entity_pool[e];

  camera.view.setCenter(static_cast<float>(game.window_width) / 2,
                        static_cast<float>(game.window_height) / 2);
  camera.view.setSize(game.window_width, game.window_height);
  game.window.setView(camera.view);
  camera.entity->position.x = static_cast<float>(game.window_width) / 2;
  camera.entity->position.y = static_cast<float>(game.window_height) / 2;
}

void update_camera(Camera &camera) {
  integrate(*camera.entity, 0.01f);
  camera.view.setCenter(camera.entity->position.x, camera.entity->position.y);
}
