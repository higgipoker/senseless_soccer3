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
#include "input.hpp"
#include "physics.hpp"
#include "pitch.hpp"
#include "player.hpp"
#include "sprite_tools.hpp"
#include "window.hpp"
//
//
//
inline void control_ball(Ball &ball) {
  controlled_entities.insert(std::make_pair(&BallEntity, &keyboard.device));
}
//
//
//
inline void control_player(Player &player, Gamepad &gamepad) {
  controlled_entities.insert(std::make_pair(&PlayerEntity, &keyboard.device));
  controlled_entities.insert(std::make_pair(&PlayerEntity, &gamepad.device));
}
//
//
//
inline void control_camera(Camera &camera) {
  controlled_entities.insert(std::make_pair(camera.entity, &keyboard.device));
}
//
//
//
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
//
//
//
static void step_sim(float timestep) {
  for (auto i = 0; i < used_entity_count; ++i) {
    integrate_improved_euler(entity_pool[i], timestep);
    // integrate_euler(entity_pool[i], timestep);
  }
}
//
//
//
inline void update_debug(Game &game) {
  if (pending_debug_toggle) {
    game.debug = !game.debug;
    pending_debug_toggle = false;
  }
  if (game.debug) {
    update_debug(game.window);
  }
}
//
//
//
inline void update_entities(Ball &ball, std::vector<Player> &players,
                            Pitch &pitch, Camera &camera) {
  update_players(players, ball);
  update_pitch(pitch, camera);
  update_ball(ball);
}
//
//
//
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
                    BALL_SPRITE_HEIGHT, 6, 0, BALL_SPRITE_FRAMES);
    BallSprite.setOrigin(BALL_SPRITE_WIDTH / 2, BALL_SPRITE_HEIGHT / 2);
    BALL_SHADOW_SPRITE(ball).setOrigin(BALL_SPRITE_WIDTH / 2,
                                       BALL_SPRITE_HEIGHT / 2);
    init_ball_animations();

    BallSprite.setTextureRect(ball_frames[4]);
    BallSprite.rotate(45);
    start_ball_animation(ball, BallAnimation::RollLeft);
    BallEntity.position.x = BALL_SPRITE_WIDTH / 2;
    BallEntity.position.y = 50;

    // set up initial perspective for shadow (doesnt change)
    BALL_SHADOW_SPRITE(ball).setTextureRect(ball_frames[7]);
    perspectivize(BallSprite, BallEntity.position.z,
                  ball.collidable.getRadius() * 2, 20);
    BALL_SHADOW_SPRITE(ball).setScale(BallSprite.getScale().x,
                                      BallSprite.getScale().y);

    ball.collidable.setOrigin(ball.collidable.getRadius() / 2,
                              ball.collidable.getRadius() / 2);
  }

  // --------------------------------------------------
  //
  // pitch
  Pitch pitch;
  init_pitch(pitch, grass_tile, camera);

  // --------------------------------------------------
  //
  // players
  std::vector<Player> players;
  for (int i = 0; i < 11; ++i) {
    Player player;
    init_player(player);
    players.emplace_back(player);
  }
  players[0].shirt_number = 1;
  populate_frames(player_frames, PLAYER_SPRITESHEET_COLS, PLAYER_SPRITE_WIDTH,
                  PLAYER_SPRITE_HEIGHT, 0, 0, PLAYER_SPRITE_FRAMES);
  populate_frames(player_shadow_frames, PLAYER_SPRITESHEET_COLS,
                  PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 3, 0,
                  PLAYER_SPRITE_FRAMES);
  init_player_animations();

  int x = 0;
  for (auto &player : players) {
    // player
    PlayerSprite.move(x, 0);
    int f = rand() % PLAYER_SPRITE_FRAMES;
    PlayerSprite.setTextureRect(player_frames[f]);
    PlayerEntity.position.x = x;
    x += 32;
    start_player_animation(player, PlayerAnimationType::Stand,
                           Direction::SOUTH);
    PlayerSprite.setOrigin(PLAYER_SPRITE_WIDTH / 2, PLAYER_SPRITE_HEIGHT);

    // shaodw
    PlayerShadowSprite.setOrigin(PLAYER_SPRITE_WIDTH / 2, PLAYER_SPRITE_HEIGHT);
    PlayerShadowSprite.setTextureRect(player_shadow_frames[0]);
    perspectivize(PlayerSprite, PlayerEntity.position.z,
                  PlayerSprite.getLocalBounds().width, 50);
    PlayerShadowSprite.setScale(PlayerSprite.getScale().x,
                                PlayerSprite.getScale().y);
  }

  // --------------------------------------------------
  //
  // gamepad
  Gamepad gamepad;
  init_gamepad(gamepad);
  gamepads.insert(&(gamepad));
  //  control_ball(ball);
  control_player(players[0], gamepad);
  // control_camera(camera);

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

    update_debug(game);

    handle_input(game, camera);
    update_camera(camera, game.world_rect);
    update_entities(ball, players, pitch, camera);
    update_animations();
    if (!sprite_pool_sorted) {
      sort_sprite_pool();
    }
  
    // (time_left(framerate) >= 0) {
      step_sim(game.timestep);
    //}
    render(game.window, camera, game.debug);

    on_frame_ended(framerate);
  }
  //  end main loop
  // --------------------------------------------------

  // --------------------------------------------------
  //
  // cleanup
#ifndef NDEBUG
  shutdown_debug();
#endif

  // only testing, the os will do this and quit the program faster
  release_sprite(BallEntity.sprite);
  release_entity(pitch.grass.entity);
  release_entity(camera.entity->id);

  if (ball.inited) {
    release_sprite(BallShadowEntity.sprite);
    release_entity(ball.shadow_entity);

    release_sprite(BallEntity.sprite);
    release_entity(ball.entity);
  }
  release_players(players);
  // delete_textures();

  std::cout << std::endl;
  std::cout << "entities still in use:\t" << used_entity_count << std::endl;
  std::cout << "sprites still in use:\t" << used_sprite_count << std::endl;
  std::cout << std::endl;
  return 0;
}
