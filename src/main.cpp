#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball/ball.hpp"
#include "globals.hpp"

#include <gamelib3/graphics/renderable.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <gamelib3/engine/engine.hpp>
#include <gamelib3/physics/movable.hpp>
#include <gamelib3/utils/files.hpp>

#include <iostream>
using namespace gamelib3;
using namespace senseless_soccer3;

class TiledBackground : public gamelib3::Renderable {
 public:
  TiledBackground(const std::string& imagefile, const sf::IntRect& world_rect) {
    tex.loadFromFile(imagefile);
    tex.setRepeated(true);
    sprite.setTexture(tex);
    sprite.setTextureRect(world_rect);
    zorder = 0;
  }
  virtual void Render(sf::RenderTarget& target) override {
    target.draw(sprite);
  }

 protected:
  sf::Texture tex;
  sf::Sprite sprite;
};

class Pitch : public Movable {
  virtual void Step(float dt) override {}
};

class BallSprite : public Renderable {
 public:
  virtual void Render(sf::RenderTarget& target) override {}
};

int main() {
  Engine engine;
  engine.Init("name", 800, 600, false);
  static const int world_width = 1600;
  static const int world_height = 1200;

  std::vector<std::string> grasses = {
      "grass_checked",    "grass_dry",   "grass_hard",
      "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

  TiledBackground grass_renderable(
      GFX_FOLDER + grasses.at(1) + ".png",
      sf::IntRect(0, 0, world_width, world_height));
  Pitch dummy;
  GameEntity grass(&dummy, &grass_renderable);
  engine.AddEntity(&grass);

  Ball ball;
  BallSprite bs;
  GameEntity ball_entity(&ball, &bs);
  engine.AddEntity(&ball_entity);

  float x = 800 / 2;
  float y = 600 / 2;
  sf::View v(sf::FloatRect(0, 0, 800, 600));
  engine.window.setView(v);

  while (engine.running) {
    v.setCenter(x, y);
    x += 1;
    engine.camera.viewport = v;
    engine.Step();
  }

  return 0;
}
