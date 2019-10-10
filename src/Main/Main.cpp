#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Folder.hpp"
#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerSprite.hpp"

using namespace Engine;
//
//
//
int main() {
  sf::IntRect window_dimensions;
  window_dimensions.left = 0;
  window_dimensions.top = 0;
  window_dimensions.width = 800;
  window_dimensions.height = 600;
  GameEngine engine("senseless soccer", window_dimensions.width,
                        window_dimensions.height);

  WorkingFolder working_folder;
  const std::string gfx_folder = working_folder.getPath() + "/gfx/";

  Match match;

  // grass texture
  auto tex_grass = std::make_shared<sf::Texture>();
  tex_grass->loadFromFile(gfx_folder + "grass_checked.png");

  // player and ball texture
  auto tex_playerandball = std::make_shared<sf::Texture>();
  tex_playerandball->loadFromFile(gfx_folder + "playerandball.png");

  sf::IntRect world{0, 0, 2000, 3000};
  Pitch pitch(tex_grass, world);
  engine.addDrawable(pitch, engine.getBackgroundLayer());

  PlayerShadowSprite shadow(tex_playerandball);
  BallShadowSprite ball_shadow(tex_playerandball);

  // sprite layer (sortable)
  int sprite_layer_id = engine.addLayer(true);
  PlayerSprite sprite1(tex_playerandball);

  Player player(sprite1, shadow);

  BallSprite ballsprite(tex_playerandball);
  Ball ball(ballsprite, ball_shadow);
  ball.attachInput(engine.getDefaultKeyboard());
  match.ball = &ball;
  match.ball->movable.setPosition({200, 200, 0});
  match.ball->sprite.move(109, 134);

  player.movable.setPosition({100, 120});

  engine.addEntity(player, sprite_layer_id);
  engine.addEntity(ball, sprite_layer_id);
  Player::match = &match;

  player.brain.activate();

  while (engine.isRunning()) {
    engine.step();
  }

  return 0;
}
