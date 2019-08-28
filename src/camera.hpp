#pragma once

#include "game.hpp"
#include "entity.hpp"

#include <SFML/Graphics/View.hpp>

struct Camera {
  Entity *entity = nullptr;
  sf::View view;
};

void init_camera(Camera &camera, Game &game) ;

void update_camera(Camera &camera);
