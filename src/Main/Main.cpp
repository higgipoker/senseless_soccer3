
#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/System.hpp>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Controls/Joysticker.hpp"
#include "Engine/EntityFactory.h"
#include "Engine/Folder.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/Texture.hpp"
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include "Pitch/MiniMapSprite.h"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerSprite.hpp"
#include "Team/PositionFactory.h"
#include "Team/Team.hpp"
#include "Team/TeamFactory.hpp"
//
//
//
using namespace Senseless;
void threadCallback(int id, bool *in) {
  static std::mutex mutex;
  int i = 0;
  int cnt = 0;
  while (i < 1000000) {
    // while (*in) {
    const std::lock_guard<std::mutex> lock(mutex);
    cnt = i / 0.3F;
    ++cnt;
    ++i;
    //    std::cout << "thread " << id << " is doing work..." << std::endl;
  }

  std::cout << "thread " << id << " done" << std::endl;
}

using namespace Senseless;
//
//
//
int main(int argc, char **args) {
  srand(static_cast<unsigned int>(time(nullptr)));
  //
  // thread test
  //
  //    bool running     = true;
  //    const int num_threads = 10;
  //    std::array<std::thread, num_threads> threads;
  //    for (int i = 0; i < num_threads; ++i) {
  //        threads.at(i) = std::thread(threadCallback, i + 1, &running);
  //    }
  //
  // game resources
  //
  WorkingFolder working_folder;
  Folder graphics_folder(working_folder.getPath() + "/gfx");
  Folder data_folder(working_folder.getPath() + "/data");
  EntityFactory entity_factory;
  TeamFactory team_factory;
  PositionFactory positions;
  //
  // engine
  //
  sf::IntRect wnd_size{0, 0, 1280, 720};
  Camera &camera = entity_factory.newCamera(wnd_size.width, wnd_size.height);
  GameEngine engine(camera, "senseless soccer", wnd_size.width,
                    wnd_size.height);
  //
  // entities
  //
  Match match(KitFactory::makeDefaultRedKit(),
              KitFactory::makeDefaultBlueKit());
  Ball &ball = entity_factory.newBall(match.getMatchTexture());
  Pitch &pitch = entity_factory.newPitch(graphics_folder.getPath(true) +
                                         "grass_checked.png");
  MiniMap &minimap =
      entity_factory.newMiniMap(match.getHomeTeam(), match.getAwayTeam(), ball,
                                pitch, engine.getMainCamera());
  //
  // gamestate
  //
  GameState gamestate(match, match.getHomeTeam(), match.getAwayTeam(), ball,
                      pitch, minimap);
  Entity::gamestate = &gamestate;
  engine.getDebugUI().gamestate = &gamestate;
  //
  // config entities
  //

  camera.setWorldRect(world);
  camera.follow(ball);
  ball.renderable.sprite->setPerspectivizable(true);
  ball.name = "Ball";
  ball.movable.position = gamestate.pitch->toScreenSpace(
      {gamestate.pitch->getDimensions().center_spot.getCenter().x,
       gamestate.pitch->getDimensions().center_spot.getCenter().y});
  ball.movable.position.z = 50;
  minimap.name = "mini map";
  minimap.movable.position = {10, 10};
  auto right_center_forward = positions.newCenterForward(
      pitch, match.getHomeTeam(), match.getAwayTeam());
  right_center_forward->applyModifier(PositionModifier::Right);
  right_center_forward->name = "Right Center Forward";
  Player &player =
      entity_factory.newPlayer(match.getMatchTexture(), TeamStrip::Home);
  player.name = right_center_forward->name;
  player.setPlayingPosition(std::move(right_center_forward));
  player.movable.position = pitch.toScreenSpace(
      {0, pitch.getDimensions().halfway_line.getPosition().y});
  player.my_team = &match.getHomeTeam();
  player.other_team = &match.getAwayTeam();

  match.getHomeTeam().setAttackingGoal(Direction::North);
  match.getHomeTeam().gameplan.defensive_line_height =
      DefensiveLineType::Normal;
  match.getHomeTeam().gameplan.defensive_width_type =
      DefensivewidthType::Normal;
  match.getHomeTeam().setAttackingState(AttackingState::Attacking);

  match.getAwayTeam().setAttackingGoal(Direction::South);
  match.getAwayTeam().gameplan.defensive_line_height =
      DefensiveLineType::Normal;
  match.getAwayTeam().gameplan.defensive_width_type =
      DefensivewidthType::Normal;
  match.getAwayTeam().setAttackingState(AttackingState::Defending);

  match.getHomeTeam().addPlayer(&player);
  match.getHomeTeam().goToSetPiecePositions(Situation::KickOff);

  //
  // add entities to engine
  //
  engine.addEntity(pitch, engine.getBackgroundLayer());
  engine.addEntity(minimap, engine.getHudLayer());
  engine.addEntity(ball, engine.getDefaultLayer());
  for (size_t i = 0; i <  match.getHomeTeam().numberPlayers(); ++i) {
    engine.addEntity(match.getHomeTeam().getPlayer(i));
    engine.addControllable(match.getHomeTeam().getPlayer(i));
  }
  for (size_t i = 0; i <  match.getAwayTeam().numberPlayers(); ++i) {
    engine.addEntity( match.getAwayTeam().getPlayer(i));
    engine.addControllable( match.getAwayTeam().getPlayer(i));
  }

  //
  // main loop
  //
  while (engine.isRunning()) {
    match.step();
    engine.step();
  }
  //    running = false;
  //    for (int i = 0; i < num_threads; ++i) {
  //        threads.at(i).join();
  //    }

  if (argc) {
    std::cout << args[0] << " exited normally" << std::endl;
  }
  return 0;
}
