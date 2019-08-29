#pragma once
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const int WORLD_WIDTH = WINDOW_WIDTH * 2;
static const int WORLD_HEIGHT = WINDOW_HEIGHT * 3;

/**
 * @brief The Game struct
 */
struct Game {
  sf::RenderWindow window;
  bool game_running = true;
  std::string window_title = "Senseless Soccer 3";
  sf::IntRect window_rect = sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  sf::IntRect world_rect = sf::IntRect(0, 0, WORLD_WIDTH, WORLD_HEIGHT);

  // target fps
  float fps = 60.0f;

  // target frame time
  float target_frame_time = 1.0f / fps;

  // physics timestep
  float timestep = 0.01f;
};
/**
 * @brief init
 * @param game
 */
void init(Game &game);
