#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball.hpp"
#include "camera.hpp"
#include "data.hpp"
#include "debug.hpp"
#include "framerate.hpp"
#include "game.hpp"
#include "gamepad.hpp"
#include "globals.hpp"
#include "grass.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "player.hpp"
#include "sprite_tools.hpp"
#include "window.hpp"

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------]
static void render(sf::RenderWindow &window, Camera &camera, bool debug) {
  window.clear(sf::Color::Blue);

  window.setView(camera.view);
  for (auto i = 0; i < used_sprite_count; ++i) {
    window.draw(sprite_pool[i]);
  }
  if (debug) {
    render_debug(window);
  }

  window.display();
}

// -----------------------------------------------------------------------------
// step_sim
// -----------------------------------------------------------------------------
static void step_sim(float timestep) {
  for (auto i = 0; i < used_entity_count; ++i) {
    // integrate_improved_euler(entity_pool[i], timestep);
    integrate_euler(entity_pool[i], timestep);
  }
}

// -----------------------------------------------------------------------------
// update_players
// -----------------------------------------------------------------------------
static void update_players(std::vector<Player> &players) {
  for (auto &player : players) {
    think(player);
    get_sprite(player).setPosition(get_player_entity(player).position.x,
                                   get_player_entity(player).position.y);
  }
  update_animations();
}

inline void check_for_debug(Game &game) {
  if (pending_debug_toggle) {
    game.debug = !game.debug;
    pending_debug_toggle = false;
  }
  if (game.debug) {
    update_debug(game.window);
  }
}

inline void update_entities(Ball &ball, std::vector<Player> &players,
                            Grass &grass, Camera &camera) {
  update_ball(ball);
  update_players(players);
  update_grass(grass, camera);
}

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  // --------------------------------------------------
  //
  // game
  Game game;
  init(game);
  Framerate framerate;
  init(framerate, game.target_frame_time);
  Camera camera;
  init_camera(camera, game);

  // --------------------------------------------------
  //
  // ball
  Ball ball;
  if (init_ball(ball) == 0) {
    ball.inited = true;
    populate_frames(ball_frames, BALL_SPRITESHEET_COLS, BALL_SPRITE_WIDTH,
                    BALL_SPRITE_HEIGHT, 3, 0, BALL_SPRITE_FRAMES);
    get_sprite(ball).setTextureRect(ball_frames[0]);
    get_sprite(ball).move(0, 60);
    start_ball_animation(ball, BallAnimation::RollLeft);
  }

  // --------------------------------------------------
  //
  // grass
  Grass grass;
  init_grass(grass, camera);

  // --------------------------------------------------
  //
  // players
  std::vector<Player> players;
  init_players(players);
  populate_frames(player_frames, PLAYER_SPRITESHEET_COLS, PLAYER_SPRITE_WIDTH,
                  PLAYER_SPRITE_HEIGHT, 0, 0, PLAYER_SPRITE_FRAMES);
  int x = 0;
  srand(time(nullptr));
  for (auto &player : players) {
    get_sprite(player).move(x, 0);
    int f = rand() % PLAYER_SPRITE_FRAMES;
    get_sprite(player).setTextureRect(player_frames[f]);
    x += 32;

    int a = (rand() % 8) + 8;
    start_player_animation(player, static_cast<PlayerAnimation>(a));
  }

  // --------------------------------------------------
  //
  // gamepad
  Gamepad gamepad;
  init_gamepad(gamepad);
  gamepads.insert(&(gamepad));
  // controlled_entities.insert(std::make_pair(&get_ball_entity(ball),
  // &gamepad));
  //  controlled_entities.insert(
  //      std::make_pair(&get_player_entity(players[0]), &gamepad));

  controlled_entities.insert(
      std::make_pair(&get_player_entity(players[0]), &keyboard.device));

  // controlled_entities.insert(std::make_pair(camera.entity, &gamepad.device));
  // controlled_entities.insert(std::make_pair(camera.entity,
  // &keyboard.device));

#ifndef NDEBUG
  // --------------------------------------------------
  //
  // debug
  init_debug(game.window);
#endif

  // --------------------------------------------------
  //
  // main loop
  //
  while (game.game_running) {
    on_frame_started(framerate);

    check_for_debug(game);

    handle_input(game, camera);
    update_camera(camera, game.world_rect);
    update_entities(ball, players, grass, camera);
    if (!sprite_pool_sorted) {
      sort_sprite_pool();
    }
    render(game.window, camera, game.debug);
    while (time_left(framerate) >= 0) {
      step_sim(game.timestep);
    }

    on_frame_ended(framerate);
  }
  //  end main loop
  // --------------------------------------------------

  // --------------------------------------------------
  //
  // cleanup
#ifndef NDEBUG
  clean_debug();
#endif

  release_texture(grass.spritesheet);
  release_texture(ball.spritesheet);

  // only testing, the os will do this and quite the program faster
  release_sprite(get_ball_entity(grass).sprite);
  release_entity(grass.entity);
  release_entity(camera.entity->id);

  if (ball.inited) {
    release_sprite(get_ball_entity(ball).sprite);
    release_entity(ball.entity);
  }
  release_players(players);
  delete_textures();

  std::cout << std::endl;
  std::cout << "entities still in use:\t" << used_entity_count << std::endl;
  std::cout << "sprites still in use:\t" << used_sprite_count << std::endl;
  std::cout << std::endl;
  return 0;
}
