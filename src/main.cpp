#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball.hpp"
#include "data.hpp"
#include "framerate.hpp"
#include "game.hpp"
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
static void render(sf::RenderWindow &window) {
  window.clear(sf::Color::Blue);
  if (sprite_pool_unsorted) {
    sort_sprite_pool();
  }
  for (auto i = 0; i < used_sprite_count; ++i) {
    window.draw(sprite_pool[i]);
  }

  window.display();
}

// -----------------------------------------------------------------------------
// step_sim
// -----------------------------------------------------------------------------
static void step_sim(float timestep) {
  for (auto i = 0; i < used_entity_count; ++i) {
    Physics::integrate(entity_pool[i], timestep);
  }
}

// -----------------------------------------------------------------------------
// update_players
// -----------------------------------------------------------------------------
static void update_players(std::vector<Player> &players) {
  for (auto &player : players) {
    think(player);
  }
  update_animations();
}

// -----------------------------------------------------------------------------
// update_ball
// -----------------------------------------------------------------------------
static void update_ball(Ball &ball) {
  apply_forces(ball);
  get_sprite(ball).setPosition(get_entity(ball).position.x,
                               get_entity(ball).position.y);
  set_sprite_z(sprite_pool[get_entity(ball).sprite], rand() % 20);
}

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  // --------------------------------------------------
  //
  // game
  //
  // --------------------------------------------------
  Game game;
  init(game);
  Framerate framerate;
  init(framerate, game.target_frame_time);

  // --------------------------------------------------
  //
  // grass
  //
  // --------------------------------------------------
  Grass grass;
  init_grass(grass, 0, 0, game.window_width, game.window_height);

  // --------------------------------------------------
  //
  // players
  //
  // --------------------------------------------------
  std::vector<Player> players;
  init_players(players);
  populate_frames(player_frames, PLAYER_SPRITESHEET_COLS, PLAYER_SPRITE_WIDTH,
                  PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_FRAMES);
  int x = 0;
  srand(time(nullptr));
  for (auto &player : players) {
    get_sprite(player).move(x, 0);
    int f = rand() % PLAYER_SPRITE_FRAMES;
    get_sprite(player).setTextureRect(player_frames[f]);
    x += 32;

    int a = (rand() % 8) + 8;
    start_animation(player, static_cast<PlayerAnimations::AnimationID>(a));
  }

  // --------------------------------------------------
  //
  // ball
  //
  // --------------------------------------------------
  Ball ball;
  if (init_ball(ball) == 0) {
    ball.inited = true;
    populate_frames(ball_frames, BALL_SPRITESHEET_COLS, BALL_SPRITE_WIDTH,
                    BALL_SPRITE_HEIGHT, BALL_SPRITE_FRAMES);
    get_sprite(ball).setTextureRect(ball_frames[0]);
    get_sprite(ball).move(0, 60);
    // get_entity(ball).force = gamelib3::Vector3(1, 0);
  }

  // --------------------------------------------------
  //
  // gamepad
  //
  // -------------------------------------------------
  Gamepad gamepad;
  init(gamepad);
  controllers.insert(&gamepad);
  controlled_entities.insert(std::make_pair(&get_entity(ball), &gamepad));

  // --------------------------------------------------
  //
  // main loop
  //
  // --------------------------------------------------
  while (game.game_running) {
    on_frame_started(framerate);

    handle_input(game);
    render(game.window);

    update_ball(ball);
    update_players(players);

    while (time_left(framerate) >= 0) {
      step_sim(game.timestep);
    }

    on_frame_ended(framerate);
  }

  // --------------------------------------------------
  //
  // cleanup
  //
  // --------------------------------------------------
  // only testing, the os will do this and quite the program faster
  release_sprite(get_entity(grass).sprite);
  release_entity(grass.entity);

  if (ball.inited) {
    release_sprite(get_entity(ball).sprite);
    release_entity(ball.entity);
  }

  release_players(players);
  cleanup();

  std::cout << std::endl;
  std::cout << "entities still in use:\t" << used_entity_count << std::endl;

  std::cout << "sprites still in use:\t" << used_sprite_count << std::endl;
  std::cout << std::endl;
  return 0;
}
