#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <sstream>

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Controls/Joysticker.hpp"
#include "Engine/Folder.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/Types.hpp"
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerFactory.hpp"
#include "Player/PlayerSprite.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
int main(int argc, char **args) {
  //
  // args
  //
  if (argc > 1) {
    std::cout << argc - 1 << " args: ";
    for (int i = 1; i < argc; ++i) {
      std::cout << args[i];
      if (i != argc - 1) {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
  //
  // game resources
  //
  WorkingFolder working_folder;
  Folder graphics_folder(working_folder.getPath() + "/gfx");
  Folder data_folder(working_folder.getPath() + "/data");
  //
  // gfx
  //
  SharedPtr<sf::Texture> tex_grass = std::make_shared<sf::Texture>();
  tex_grass->loadFromFile(graphics_folder.getPath(true) + "grass_checked.png");
  SharedPtr<sf::Texture> tex_playerandball = std::make_shared<sf::Texture>();
  tex_playerandball->loadFromFile(graphics_folder.getPath(true) +
                                  "playerandball.png");
  //
  // engine
  //
  sf::IntRect wnd_size{0, 0, 1280, 730};
  GameEngine engine("senseless soccer", wnd_size.width, wnd_size.height);
  int sprite_layer_id = engine.addLayer(true);
  //
  // ball
  //
  UniquePtr<Sprite> ballsprite =
      std::make_unique<BallSprite>(tex_playerandball);
  UniquePtr<Sprite> ball_shadow =
      std::make_unique<BallShadowSprite>(tex_playerandball);
  ballsprite->setPerspectivizable(true);
  auto ball =
      std::make_unique<Ball>(std::move(ballsprite), std::move(ball_shadow));

  //
  // pitch
  //
  engine.getMainCamera().setWorldRect(world);
  UniquePtr<Sprite> pitch = std::make_unique<Pitch>(tex_grass, world);
  engine.addSprite(*pitch.get(), engine.getBackgroundLayer());
  //
  // match and teams
  //
  Match match;
  match.setPitch(std::move(pitch));
  match.setBall(std::move(ball));
  match.getBall().movable.setPosition(
      match.getPitch().dimensions.center_spot.getCenter());
  engine.addEntity(match.getBall(), sprite_layer_id);
  engine.getMainCamera().follow(match.getBall());
  UniquePtr<Team> team1 = std::make_unique<Team>();
  UniquePtr<Team> team2 = std::make_unique<Team>();
  Team::match = &match;
  match.addTeams(std::move(team1), std::move(team2));

  //
  // players
  //
  Player::connectMatch(match);
  for (auto i = 0; i < 10; ++i) {
    UniquePtr<Player> player = PlayerFactory::makePlayer(tex_playerandball);
    TeamData td;
    td.shirt_number = i + 1;
    player->setTeamData(td);
    player->movable.setPosition(
        match.getPitch().dimensions.center_spot.getCenter().x + (i * 10),
        match.getPitch().dimensions.center_spot.getCenter().y - 50);
    player->support_type = i;
    engine.addEntity(*player, sprite_layer_id);
    engine.addControllable(*player);
    player->getBrain().changeState(brain_state::Support);
    std::stringstream ss;
    ss << "player" << i + 1;
    player->name = ss.str();
    match.getHomeTeam().addPlayer(std::move(player));
  }
  if (match.getHomeTeam().hasPlayers()) {
    // match.getHomeTeam().getPlayer().attachInput(engine.getDefaultGamepad());
  }
  match.getHomeTeam().attachInputDevice(engine.getDefaultGamepad());
  match.getHomeTeam().getPlayer().getBrain().changeState(brain_state::Retrieve);

  // test
  ProgressBar bar(40, 3, 50);
  match.getHomeTeam().getPlayer().power_bar = &bar;
  engine.addSprite(bar, sprite_layer_id);

  srand(time(NULL));

  Joysticker joysticker;
  joysticker.input = &engine.getDefaultGamepad();
  joysticker.team = &match.getHomeTeam();
  joysticker.power_bar = &bar;
  engine.getDefaultGamepad().attachListener(joysticker);
  while (engine.isRunning()) {
    engine.step();
    match.update();
    joysticker.update();
  }

  std::cout << args[0] << " exited normally" << std::endl;
  return 0;
}
