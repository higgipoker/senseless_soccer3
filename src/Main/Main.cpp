#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Folder.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerSprite.hpp"
//
//
//
int main() {
  sf::IntRect window_dimensions;
  window_dimensions.left = 0;
  window_dimensions.top = 0;
  window_dimensions.width = 800;
  window_dimensions.height = 600;
  Engine::Engine engine("senseless soccer", window_dimensions.width,
                        window_dimensions.height);

  Engine::WorkingFolder working_folder;
  const std::string gfx_folder = working_folder.getPath() + "/gfx/";

  // grass texture
  auto tex_grass = std::make_shared<sf::Texture>();
  tex_grass->loadFromFile(gfx_folder + "grass_checked.png");

  // player and ball texture
  auto tex_playerandball = std::make_shared<sf::Texture>();
  tex_playerandball->loadFromFile(gfx_folder + "playerandball.png");

  // bg layer
  int bg_layer_id = engine.addLayer(false);
  sf::IntRect world{0, 0, 2000, 3000};
  Pitch pitch(tex_grass, world);
  engine.addDrawable(&pitch, bg_layer_id);

  // shadow layer
  int shadow_layer_id = engine.addLayer(false);
  PlayerShadowSprite shadow(tex_playerandball);
  engine.addDrawable(&shadow, shadow_layer_id);

  BallShadowSprite ball_shadow(tex_playerandball);
  engine.addDrawable(&ball_shadow, shadow_layer_id);


  // sprite layer (sortable)
  int sprite_layer_id = engine.addLayer(true);
  PlayerSprite sprite1(tex_playerandball);
  engine.addDrawable(&sprite1, sprite_layer_id);

  Player player;
  player.sprite = &sprite1;
  player.shadow = &shadow;
  player.animate(PlayerAnimationType::Run, Engine::Direction::SOUTH);

  Ball ball;
  BallSprite ballsprite(tex_playerandball);
  ball.sprite = &ballsprite;
  ball.shadow = &ball_shadow;
  ball.sprite->move(100, 0);
  engine.addDrawable(&ballsprite, sprite_layer_id);

  while (engine.isRunning()) {
    // updat game stuff
    player.update();
    ball.update();

    // step the engine
    engine.step();
  }

  return 0;
}
