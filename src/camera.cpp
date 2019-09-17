#include "camera.hpp"
#include "data.hpp"
#include "debug.hpp"
#include "entity.hpp"
#include "physics.hpp"

#include <iostream>
//
// init_camera
//
void init_camera(Camera &camera, Game &game) {
  int e = acquire_entity();
  camera.entity = &entity_pool[e];
  camera.entity->speed = 1;
  camera.entity->co_friction = 0.01f;
  camera.entity->type = EntityType::Camera;
  camera.view.setCenter(static_cast<float>(game.window_rect.width) / 2,
                        static_cast<float>(game.window_rect.height) / 2);
  camera.entity->position.x = static_cast<float>(game.window_rect.width) / 2;
  camera.entity->position.y = static_cast<float>(game.window_rect.height) / 2;
  camera.view.setSize(game.window_rect.width, game.window_rect.height);
  game.window.setView(camera.view);

  camera.inner_circle.setRadius(camera.view.getSize().x / 7);
  camera.inner_circle.setPosition(
      camera.view.getCenter().x - camera.inner_circle.getRadius(),
      camera.view.getCenter().y - camera.inner_circle.getRadius());

  camera.inner_circle.setFillColor(sf::Color::Transparent);
  camera.inner_circle.setOutlineThickness(2);
  camera.inner_circle.setOutlineColor(sf::Color::Blue);
}
//
// update_camera
//
void update_camera(Camera &camera, sf::IntRect world_rect) {
  camera.view.setCenter(camera.entity->position.x, camera.entity->position.y);
  auto track = camera_tracking.find(&camera);
  if (track != camera_tracking.end()) {
    camera.inner_circle.setPosition(
        camera.view.getCenter().x - camera.inner_circle.getRadius(),
        camera.view.getCenter().y - camera.inner_circle.getRadius());

    debug_shapes.emplace_back(&camera.inner_circle);

    static const float f = 1.0f;
    if (!circle_contains_point(camera.inner_circle, track->second->position)) {
      Vector3 camera_center = Vector3::fromSfVector(camera.view.getCenter());
      Vector3 direction_to_target =
          track->second->position - camera_center;
      direction_to_target = direction_to_target.normalise();


      float target_speed = track->second->velocity.magnitude();
      apply_force(*camera.entity, direction_to_target * f * target_speed);
    }
  }

  // clamp_camera(camera, world_rect);
}
//
// clamp_camera
//
void clamp_camera(Camera &camera, sf::IntRect bounds) {
  int act_x = camera.entity->position.x - camera.view.getSize().x / 2;
  int act_y = camera.entity->position.y - camera.view.getSize().y / 2;

  bool bound = false;

  if (act_x < bounds.left) {
    camera.entity->velocity.reset();
    //    act_x = bounds.left;
    //    camera.entity->velocity.x = -camera.entity->velocity.x * 0.8f;
    bound = true;
  } else if (act_y < bounds.top) {
    act_y = bounds.top;
    camera.entity->velocity.y = -camera.entity->velocity.y * 0.8f;
    bound = true;
  }

  else if (act_x + camera.view.getSize().x > bounds.left + bounds.width) {
    act_x = bounds.left + bounds.width - camera.view.getSize().x;
    camera.entity->velocity.x = -camera.entity->velocity.x * 0.8f;
    bound = true;

  } else if (act_y + camera.view.getSize().y > bounds.top + bounds.height) {
    act_y = bounds.top + bounds.height - camera.view.getSize().y;
    camera.entity->velocity.y = -camera.entity->velocity.y * 0.8f;
    bound = true;
  }

  if (bound) {
    camera.entity->force.reset();
    camera.entity->position = Vector3(act_x + camera.view.getSize().x / 2,
                                      act_y + camera.view.getSize().y / 2);
  }
}
//
//
//
void camera_follow(Camera &camera, Entity &entity) {
  camera_tracking.insert(std::make_pair(&camera, &entity));
  camera.entity->position = entity.position;
  camera.view.setCenter(camera.entity->position.x, camera.entity->position.y);
}
