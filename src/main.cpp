#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ball.hpp"
#include "entity.hpp"
#include "globals.hpp"
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

static const std::array<std::string, 6> grasses{
    "grass_checked",    "grass_dry",   "grass_hard",
    "grass_horizontal", "grass_plain", "grass_plain_horizontal"};

const std::string grass_tile{Globals::GFX_FOLDER + grasses.at(0) + ".png"};
Entity::SortableSprite *grass = Entity::acquire_sprite();
sf::View camera;

// -----------------------------------------------------------------------------
//
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
//
// -----------------------------------------------------------------------------]
static void render(sf::RenderWindow &window) {
  Entity::sort_sprites();
  window.clear(sf::Color::Blue);
  for (auto &sprite : Entity::sprites) {
    window.draw(sprite.sprite);
  }
  window.display();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void integrate(Entity::Entity &entity) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void step_sim() {
  for (auto &entity : Entity::entities) {
    integrate(entity);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void update_players(std::vector<Player::Player> &players) {
  for (auto &player : players) {
    Player::think(player);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void update_ball(Ball::Ball &ball) { Ball::apply_forces(ball); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
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

  // --------------------------------------------------
  //
  // players
  //
  // --------------------------------------------------
  std::vector<Player::Player> players;
  Player::init_players(players);
  Player::populate_player_sprite_frames(Player::player_frames);
  int x = 0;
  for (auto &player : players) {
    player.sprite->sprite.move(x, 0);
    int f = rand() % Player::PLAYER_SPRITE_FRAMES;
    player.sprite->sprite.setTextureRect(Player::player_frames[f]);
    x += 32;
  }

  // --------------------------------------------------
  //
  // ball
  //
  // --------------------------------------------------
  Ball::Ball ball;
  Ball::init_ball(ball);
  Ball::populate_ball_sprite_frames(Ball::ball_frames);
  ball.sprite->sprite.setTextureRect(Ball::ball_frames[0]);
  ball.sprite->sprite.move(0, 60);

  // --------------------------------------------------
  //
  // grass
  //
  // --------------------------------------------------
  sf::Texture *tex = Texture::acquire_texture(grass_tile);
  tex->setRepeated(true);
  grass->sprite.setTexture(*tex);
  grass->sprite.setTextureRect(sf::IntRect(0, 0, window_width, window_height));
  grass->z_order = -1;

  // --------------------------------------------------
  //
  // main loop
  //
  // --------------------------------------------------
  while (game_running) {
    handle_input(window);
    render(window);

    update_ball(ball);
    update_players(players);
    step_sim();
  }

  // --------------------------------------------------
  //
  // cleanup
  //
  // --------------------------------------------------
  // only testing, the os will do this and quite the program faster
  Texture::cleanup();
  return 0;
}
