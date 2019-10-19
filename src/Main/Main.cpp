#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Engine/Folder.hpp"
#include "Engine/GameEngine.hpp"
#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerFactory.hpp"
#include "Player/PlayerSprite.hpp"

using namespace Engine;
//
//
//
int main() {
  //
  // resources
  //
  WorkingFolder working_folder;
  Folder graphics_folder(working_folder.getPath() + "/gfx");
  Folder data_folder(working_folder.getPath() + "/data");
  //
  // gfx
  //
  // grass texture
  auto tex_grass = std::make_shared<sf::Texture>();
  tex_grass->loadFromFile(graphics_folder.getPath(true) + "grass_checked.png");
  // player and ball texture
  auto tex_playerandball = std::make_shared<sf::Texture>();
  tex_playerandball->loadFromFile(graphics_folder.getPath(true) +
                                  "playerandball.png");
  //
  // engine
  //
  sf::IntRect wnd_size{0, 0, 800, 600};
  GameEngine engine("senseless soccer", wnd_size.width, wnd_size.height);
  // sprite layer (sortable)
  int sprite_layer_id = engine.addLayer(true);
  //
  // match
  //
  Match match;
  //
  // players
  //
  Player::connectMatch(match);
  std::vector<std::unique_ptr<Player>> players;
  for (auto i = 0; i < 10; ++i) {
    players.push_back(PlayerFactory::makePlayer(tex_playerandball));
    TeamData td;
    td.shirt_number = i + 1;
    players.back()->setTeamData(td);
    players.back()->movable.setPosition(i * 10, 120);
    engine.addEntity(*players.back(), sprite_layer_id);
  }
  //
  // pitch
  //
  sf::IntRect world{0, 0, 2000, 3000};
  engine.getMainCamera().setWorldRect(world);
  std::unique_ptr<Sprite> pitch = std::make_unique<Pitch>(tex_grass, world);
  engine.addSprite(*pitch.get(), engine.getBackgroundLayer());
  std::unique_ptr<Sprite> ball_shadow =
      std::make_unique<BallShadowSprite>(tex_playerandball);
  //
  // ball
  //
  std::unique_ptr<Sprite> ballsprite =
      std::make_unique<BallSprite>(tex_playerandball);
  auto ball =
      std::make_unique<Ball>(std::move(ballsprite), std::move(ball_shadow));
  // ball.attachInput(engine.getDefaultKeyboard());
  // match owns the ball
  match.setBall(std::move(ball));
  match.getBall().movable.setPosition({200, 200, 0});
  engine.addEntity(match.getBall(), sprite_layer_id);

  players[0]->getBrain().changeState(brain_state::Retrieve);
  while (engine.isRunning()) {
    engine.step();
  }

  return 0;
}
