#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <gamelib3/engine/engine.hpp>
#include <gamelib3/physics/movable.hpp>

#include <iostream>
using namespace gamelib3;

struct MyPlayer {
  MyPlayer() = default;
  MyPlayer(int s) { shirt_number = s; }
  MovablePair movable;
  RenderablePair renderable;
  int shirt_number = 0;
};

int main() {
  Engine engine;
  engine.init("name", 800, 600, false);

  std::vector<MyPlayer> players;
  for (int i = 1; i <= 11; ++i) {
    MyPlayer player(i);
    player.movable.id = engine.addMovable(player.movable.entity);
    player.renderable.id = engine.addRenderable(player.renderable.entity);
    players.push_back(player);
  }

  for(auto &p : players){
     std::cout << p.shirt_number << std::endl;
  }
  while (engine.running) {
    engine.step();

  }

  return 0;
}
