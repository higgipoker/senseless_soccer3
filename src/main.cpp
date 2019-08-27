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
#include "window.hpp"

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------]
static void render(sf::RenderWindow &window) {
  window.clear(sf::Color::Blue);
  if (Data::sprite_pool_unsorted) {
    Data::sort_sprite_pool();
  }
  for (auto i = 0; i < Data::used_sprite_count; ++i) {
    window.draw(Data::sprite_pool[i]);
  }

  window.display();
}

// -----------------------------------------------------------------------------
// step_sim
// -----------------------------------------------------------------------------
static void step_sim(float timestep) {
  for (auto i = 0; i < Data::used_entity_count; ++i) {
    Physics::integrate(Data::entity_pool[i], timestep);
  }
}

// -----------------------------------------------------------------------------
// update_players
// -----------------------------------------------------------------------------
static void update_players(std::vector<Player::Player> &players) {
  for (auto &player : players) {
    Player::think(player);
  }
  Player::update_animations();
}

// -----------------------------------------------------------------------------
// update_ball
// -----------------------------------------------------------------------------
static void update_ball(Ball::Ball &ball) {
  Ball::apply_forces(ball);
  Ball::get_sprite(ball).setPosition(Ball::get_entity(ball).position.x,
                                     Ball::get_entity(ball).position.y);
  Data::sprite_pool[Ball::get_entity(ball).sprite].set_z(rand() % 20);
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
  Framerate::Framerate framerate;
  Framerate::init(framerate, game.target_frame_time);

  // --------------------------------------------------
  //
  // grass
  //
  // --------------------------------------------------
  Grass::Grass grass;
  Grass::init_grass(grass, 0, 0, game.window_width, game.window_height);

  // --------------------------------------------------
  //
  // players
  //
  // --------------------------------------------------
  std::vector<Player::Player> players;
  Player::init_players(players);
  Player::populate_player_sprite_frames(Player::player_frames);
  int x = 0;
  srand(time(nullptr));
  for (auto &player : players) {
    Player::get_sprite(player).move(x, 0);
    int f = rand() % Player::PLAYER_SPRITE_FRAMES;
    Player::get_sprite(player).setTextureRect(Player::player_frames[f]);
    x += 32;

    int a = (rand() % 8) + 8;
    Player::start_animation(player,
                            static_cast<PlayerAnimations::AnimationID>(a));
  }

  // --------------------------------------------------
  //
  // ball
  //
  // --------------------------------------------------
  Ball::Ball ball;
  if (Ball::init_ball(ball) == 0) {
    ball.inited = true;
    Ball::populate_ball_sprite_frames(Ball::ball_frames);
    Ball::get_sprite(ball).setTextureRect(Ball::ball_frames[0]);
    Ball::get_sprite(ball).move(0, 60);
    Ball::get_entity(ball).force = gamelib3::Vector3(1, 0);
  }

  // --------------------------------------------------
  //
  // gamepad
  //
  // -------------------------------------------------
  Input::Gamepad gamepad;
  Input::init(gamepad);

  // --------------------------------------------------
  //
  // main loop
  //
  // --------------------------------------------------
  while (game.game_running) {
    Framerate::on_frame_started(framerate);

    Input::handle_input(game, gamepad);
    render(game.window);

    update_ball(ball);
    update_players(players);

    while (Framerate::time_left(framerate) >= 0) {
      step_sim(game.timestep);
    }

    Framerate::on_frame_ended(framerate);
  }

  // --------------------------------------------------
  //
  // cleanup
  //
  // --------------------------------------------------
  // only testing, the os will do this and quite the program faster
  Data::release_sprite(Grass::get_entity(grass).sprite);
  Data::release_entity(grass.entity);

  if (ball.inited) {
    Data::release_sprite(Ball::get_entity(ball).sprite);
    Data::release_entity(ball.entity);
  }

  Player::release_players(players);
  Texture::cleanup();

  std::cout << std::endl;
  std::cout << "entities still in use:\t" << Data::used_entity_count
            << std::endl;

  std::cout << "sprites still in use:\t" << Data::used_sprite_count
            << std::endl;
  std::cout << std::endl;
  return 0;
}
