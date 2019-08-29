#include "camera.hpp"
#include "physics.hpp"

#include "data.hpp"
#include "entity.hpp"

#include <iostream>

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void init_camera(Camera &camera, Game &game) {
  int e = acquire_entity();
  camera.entity = &entity_pool[e];

  camera.view.setCenter(static_cast<float>(game.window_rect.width) / 2,
                        static_cast<float>(game.window_rect.height) / 2);
  camera.view.setSize(game.window_rect.width, game.window_rect.height);
  game.window.setView(camera.view);
  camera.entity->position.x = static_cast<float>(game.window_rect.width) / 2;
  camera.entity->position.y = static_cast<float>(game.window_rect.height) / 2;
  camera.entity->co_friction = 0.001f;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void update_camera(Camera &camera, sf::IntRect world_rect) {
  // integrate_euler(*camera.entity, 0.01f);
  clamp_camera(camera, world_rect);
  camera.view.setCenter(camera.entity->position.x, camera.entity->position.y);

  if (camera.entity->velocity.magnitude() > 0.25f) {
    camera.entity->velocity = camera.entity->velocity.setMagnitude(0.25f);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void clamp_camera(Camera &camera, sf::IntRect bounds) {
  int act_x = camera.entity->position.x - camera.view.getSize().x / 2;
  int act_y = camera.entity->position.y - camera.view.getSize().y / 2;

  bool bound = false;

  if (act_x < bounds.left) {
    act_x = bounds.left;
    bound = true;
  }
  if (act_y < bounds.top) {
    act_y = bounds.top;
    bound = true;
  }

  if (act_x + camera.view.getSize().x > bounds.left + bounds.width) {
    act_x = bounds.left + bounds.width - camera.view.getSize().x;
    bound = true;
  }
  if (act_y + camera.view.getSize().y > bounds.top + bounds.height) {
    act_y = bounds.top + bounds.height - camera.view.getSize().y;
    bound = true;
  }

  if (bound) {
    camera.entity->force.reset();
    camera.entity->velocity = camera.entity->velocity.reverse();
    camera.entity->position = Vector3(act_x + camera.view.getSize().x / 2,
                                      act_y + camera.view.getSize().y / 2);
  }
}
