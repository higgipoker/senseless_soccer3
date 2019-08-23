#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball/ball_movable.hpp"
#include "globals.hpp"
#include "player/player.hpp"
#include "player/player_movable.hpp"

#include <gamelib3/graphics/renderable.hpp>
#include <gamelib3/graphics/tiled_background.hpp>
#include <gamelib3/physics/metrics.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <gamelib3/engine/engine.hpp>
#include <gamelib3/input/input.hpp>
#include <gamelib3/physics/movable.hpp>
#include <gamelib3/utils/files.hpp>

#include <iostream>
using namespace gamelib3;
using namespace senseless_soccer3;

static const int world_width = 1600;
static const int world_height = 1200;

static const int window_width = 800;
static const int window_height = 600;

std::vector<std::string> grasses = {"grass_checked", "grass_dry",
                                    "grass_hard",    "grass_horizontal",
                                    "grass_plain",   "grass_plain_horizontal"};

const std::string grass_tile{GFX_FOLDER + grasses.at(0) + ".png"};

class Game : public gamelib3::InputCallback {
 public:
  Game() {}

  virtual void HandleEvent(sf::Event event) override {}

  void Run() {
    // init engine
    engine.Init("senseless soccer 3.0", window_width, window_height, false);
    engine.registerInputCallback(this);

    // pitch
    gamelib3::TiledBackground grass_renderable(grass_tile, world_rect);
    GameEntity grass(&grass_renderable);
    engine.AddEntity(&grass);

    // ball
    Ball ball;
    Sprite ballsprite(GFX_FOLDER + "ball_new.png", 4, 2);
    GameEntity ball_entity(&ball, &ballsprite);
    engine.AddEntity(&ball_entity);

    // player
    PlayerMovable player;
    Sprite playersprite(GFX_FOLDER + "player/player.png", 6, 24);
    Player player_entity(&player, &playersprite);
    engine.AddEntity(&player_entity);

    engine.gamepad.AddListener(&player_entity);
    player_entity.controller = &engine.gamepad;

    ball.SetPosition(200, 200);
    player.SetPosition(100, 100);

    player.StartAnimation("run_east");
    while (engine.running) {
      player_entity.Update();
      engine.Step();
    }
    engine.Shutdown();
  }

 private:
  Engine engine;

  const sf::IntRect world_rect{0, 0, world_width, world_height};
};

int main(int argc, char *argv[]) {
  Game senseless_soccer;
  senseless_soccer.Run();
  return 0;
}
