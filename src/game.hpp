#pragma once
#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

struct Game {
  sf::RenderWindow window;
  sf::View camera;
  bool game_running = true;
  std::string window_title = "Senseless Soccer 3";
  int world_width = 1600;
  int world_height = 1200;
  int window_width = 1280;
  int window_height = 720;

  // target fps
  float fps = 60.0f;

  // target frame time
  float target_frame_time = 1.0f / fps;

  // physics timestep
  float timestep = 0.01f;
};

inline void init(Game& game) {
  init_window(game.window, game.window_title, game.window_width,
              game.window_height, sf::Style::Default);
  init_camera(game.camera, game.window_width, game.window_height);
  game.window.setView(game.camera);
}
