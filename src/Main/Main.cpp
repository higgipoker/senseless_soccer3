#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine/Engine.hpp"
#include "Engine/Folder.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/PlayerSprite.hpp"
#include "Player/Player.hpp"
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


  // bg layer
  int bg_layer_id = engine.addLayer(false);
  Pitch pitch(gfx_folder + "grass_checked.png");
  pitch.setRect(window_dimensions);
  engine.addDrawable(&pitch, bg_layer_id);

  // sprite layer
  int sprite_layer_id = engine.addLayer(true);
  PlayerSprite sprite1(gfx_folder + "playerandball.png");
  engine.addDrawable(&sprite1, sprite_layer_id);

  PlayerSprite sprite2(gfx_folder + "playerandball.png");
  sprite2.move(40,0);
  sprite2.setFrame(1);
  engine.addDrawable(&sprite2, sprite_layer_id);

  Player player;
  player.sprite = &sprite1;
  player.animate(PlayerAnimationType::Run, Engine::Direction::NORTH);

  while (engine.isRunning()) {

    // updat game stuff
    player.sprite->animate();

    // step the engine
    engine.step();
  }

  return 0;
}
