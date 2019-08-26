#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball.hpp"
#include "data.hpp"
#include "framerate.hpp"
#include "globals.hpp"
#include "grass.hpp"
#include "physics.hpp"
#include "player.hpp"
#include "window.hpp"

#include <SFML/Window/Event.hpp>

static bool game_running = true;
static const std::string window_title = "Senseless Soccer 3";
static const int world_width = 1600;
static const int world_height = 1200;

static const int window_width = 1280;
static const int window_height = 720;

// target fps
static const float fps = 60.0f;

// target frame time
static const float target_frame_time = 1.0f / fps;

// physics timestep
static const float timestep = 0.01f;
sf::View camera;

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void handle_input(sf::RenderWindow &window) {
  static sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        game_running = false;
        break;
      case sf::Event::Resized:
        camera.setSize(event.size.width, event.size.height);
        break;
      case sf::Event::LostFocus:
        break;
      case sf::Event::GainedFocus:
        break;
      case sf::Event::TextEntered:
        break;
      case sf::Event::KeyPressed:
        if (window.hasFocus()) {
          if (event.key.code == sf::Keyboard::Escape) {
            game_running = false;
          }
        }
        break;
      case sf::Event::KeyReleased:
        break;
      case sf::Event::MouseWheelMoved:
        break;
      case sf::Event::MouseWheelScrolled:
        break;
      case sf::Event::MouseButtonPressed:
        break;
      case sf::Event::MouseButtonReleased:
        break;
      case sf::Event::MouseMoved:
        break;
      case sf::Event::MouseEntered:
        break;
      case sf::Event::MouseLeft:
        break;
      case sf::Event::JoystickButtonPressed:
        break;
      case sf::Event::JoystickButtonReleased:
        break;
      case sf::Event::JoystickMoved:
        break;
      case sf::Event::JoystickConnected:
        break;
      case sf::Event::JoystickDisconnected:
        break;
      case sf::Event::TouchBegan:
        break;
      case sf::Event::TouchMoved:
        break;
      case sf::Event::TouchEnded:
        break;
      case sf::Event::SensorChanged:
        break;
      case sf::Event::Count:
        break;
    }
  }
}

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
static void step_sim() {
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

    int f = rand() % Player::PLAYER_SPRITE_FRAMES;
    player.Sprite().setTextureRect(
        Player::player_frames[f]);
  }
}

// -----------------------------------------------------------------------------
// update_ball
// -----------------------------------------------------------------------------
static void update_ball(Ball::Ball &ball) {
  Ball::apply_forces(ball);
  ball.Sprite().setPosition(ball.Entity().position.x,
                               ball.Entity().position.y);
}

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::cout << "MEMORY NEEDED: " << Data::calc_mem_needed() << " bytes"
            << std::endl;
  // --------------------------------------------------
  //
  // window
  //
  // --------------------------------------------------
  sf::RenderWindow window;
  Window::init_window(window, window_title, window_width, window_height,
                      sf::Style::Default);
  Window::init_camera(camera, window_width, window_height);
  window.setView(camera);
  Framerate::Framerate framerate;

  // --------------------------------------------------
  //
  // grass
  //
  // --------------------------------------------------
  Grass::Grass grass;
  Grass::init_grass(grass, 0, 0, window_width, window_height);

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
    player.Sprite().move(x, 0);
    int f = rand() % Player::PLAYER_SPRITE_FRAMES;
    player.Sprite().setTextureRect(
        Player::player_frames[f]);
    x += 32;
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
    ball.Sprite().setTextureRect(
        Ball::ball_frames[0]);
    ball.Sprite().move(0, 60);
    ball.Entity().force = gamelib3::Vector3(10, 0);
  }

  for (int i = 0; i < 100; ++i) {
    // int id = Data::acquire_sprite();
  }

  // --------------------------------------------------
  //
  // main loop
  //
  // --------------------------------------------------
  while (game_running) {
    framerate.on_frame_started();

    handle_input(window);
    render(window);

    update_ball(ball);
    update_players(players);

    while (framerate.time_left(target_frame_time) >= 0) {
      step_sim();
    }

    framerate.on_frame_ended();
  }

  // --------------------------------------------------
  //
  // cleanup
  //
  // --------------------------------------------------
  // only testing, the os will do this and quite the program faster
  Data::release_sprite(grass.Entity().sprite);
  Data::release_entity(grass.entity);

  if (ball.inited) {
    Data::release_sprite(ball.Entity().sprite);
    Data::release_entity(ball.entity);
  }

  Player::release_players(players);
  Texture::cleanup();

  std::cout << "entities still in use at exit: " << Data::used_entity_count
            << std::endl;

  std::cout << "sprites still in use at exit: " << Data::used_sprite_count
            << std::endl;
  return 0;
}
