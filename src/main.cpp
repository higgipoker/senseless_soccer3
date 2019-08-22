#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball/ball.hpp"
#include "globals.hpp"

#include <gamelib3/graphics/renderable.h>
#include <gamelib3/graphics/tiled_background.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <gamelib3/engine/engine.hpp>
#include <gamelib3/physics/movable.hpp>
#include <gamelib3/utils/files.hpp>
#include <gamelib3/input/input.hpp>

#include <iostream>
using namespace gamelib3;
using namespace senseless_soccer3;

static const int world_width = 1600;
static const int world_height = 1200;

static const int window_width = 800;
static const int window_height = 600;

std::vector<std::string> grasses = {
  "grass_checked",    "grass_dry",   "grass_hard",
  "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

const std::string grass_tile {GFX_FOLDER + grasses.at(1) + ".png"};

static const sf::IntRect world_rect{0, 0, world_width, world_height};
static sf::View viewport{sf::FloatRect(0, 0, window_width, window_height)};

class Game : public gamelib3::InputCallback{
public:
  virtual void HandleEvent(sf::Event event) override{
   // std::cout << "input event happened: " << event.type << std::endl;
  }
};

int main() {
  Game game;
  Engine engine;
  engine.Init("senseless soccer 3.0", window_width, window_height, false);
  engine.registerInputCallback(&game);

  // pitch
  gamelib3::TiledBackground grass_renderable(grass_tile,world_rect);
  GameEntity grass(&grass_renderable);
  engine.AddEntity(&grass);

  // ball
  Ball ball;
  GameEntity ball_entity(&ball);
  engine.AddEntity(&ball_entity);

  int direction = 1;
  int ticks = 0;

  while (engine.running) {
    //viewport.move(1*direction,0);
    //engine.camera.viewport = viewport;
    engine.Step();
  }

  return 0;
}
