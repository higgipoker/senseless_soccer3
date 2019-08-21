#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <gamelib3/engine/engine.hpp>
#include <gamelib3/physics/movable.hpp>
#include <gamelib3/utils/files.hpp>

#include <iostream>
using namespace gamelib3;

struct MyPlayer {
  MyPlayer() = default;
  MyPlayer(int s) { shirt_number = s; }
  MovablePair movable;
  RenderablePair renderable;
  int shirt_number = 0;

  void addToEngine(Engine &engine) {
    movable.id = engine.addMovable(movable.entity);
    renderable.id = engine.addRenderable(renderable.entity);
  }
};

int main() {
  Engine engine;
  engine.init("name", 800, 600, false);

  std::vector<MyPlayer> players;
  for (int i = 1; i <= 11; ++i) {
    MyPlayer player(i);
    player.addToEngine(engine);
    players.push_back(player);
  }

  std::string dir = Files::getWorkingDirectory();

  static const int world_width = 1600;
  static const int world_height = 1200;
  Renderable grass;
  sf::Texture tex;
  tex.loadFromFile(dir + "/gfx/grass_hard.png");
  tex.setRepeated(true);
  grass.sprite.setTexture(tex);
  grass.sprite.setTextureRect(sf::IntRect(0, 0, world_width, world_height));
  engine.addRenderable(grass);

  int x = 800 / 2;
  int y = 600 / 2;
  sf::View v(sf::FloatRect(0, 0, 800, 600));
  engine.window.setView(v);

  while (engine.running) {
    v.setCenter(x, y) ;
    x+=10;
    engine.main_view = v;
    engine.window.setView(v);
    engine.step();
  }

  return 0;
}
