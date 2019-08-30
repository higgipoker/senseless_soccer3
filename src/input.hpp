#pragma once
#include "camera.hpp"
#include "game.hpp"

#include <gamelib3/math/vector.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>

#include <array>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>

constexpr unsigned char mask_zero{0};        // 0000 0001
constexpr unsigned char mask_a{1 << 0};      // 0000 0001
constexpr unsigned char mask_b{1 << 1};      // 0000 0010
constexpr unsigned char mask_x{1 << 2};      // 0000 0100
constexpr unsigned char mask_y{1 << 3};      // 0000 1000
constexpr unsigned char mask_l1{1 << 4};     // 0001 0000
constexpr unsigned char mask_r1{1 << 5};     // 0010 0000
constexpr unsigned char mask_back{1 << 6};   // 0100 0000
constexpr unsigned char mask_start{1 << 7};  // 1000 0000

constexpr unsigned char mask_dpad_up{1 << 0};      // 0000 0001
constexpr unsigned char mask_dpad_right{1 << 1};   // 0000 0010
constexpr unsigned char mask_dpad_down{1 << 2};    // 0000 0100
constexpr unsigned char mask_dpad_left{1 << 3};    // 0000 1000
constexpr unsigned char mask_stick_up{1 << 4};     // 0001 0000
constexpr unsigned char mask_stick_right{1 << 5};  // 0010 0000
constexpr unsigned char mask_stick_down{1 << 6};   // 0100 0000
constexpr unsigned char mask_stick_left{1 << 7};   // 1000 0000

static const int MAX_JOYSTICKS = 8;
static bool mouse_pressed = false;
/**
 * @brief The InputState enum
 */
enum InputState {
  Up = 0,
  Down,
  Left,
  Right,

  FireDown,
  FireUp,
  FireLength,
  FireLengthCached,
  SingleTap,
  DoubleTap,
  FirePress,

  Totalevents
};

/**
 * @brief The ControllerEventID enum
 */
enum class ControllerEventID {
  NoEvent = 0,
  Fire,
  FireTap,
  DPadLeft,
  DPadRight,
  DPadUp,
  DPadDown
};

/**
 * @brief The ControllerEventStatus enum
 */
enum class ControllerEventStatus { Released = 0, Pressed };

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
  ControllerEventID id = ControllerEventID::NoEvent;
  ControllerEventStatus status = ControllerEventStatus::Released;
  int param = 0;
};
static const int fire_tap_length = 5;
static const int fire_double_tap_length = 10;

/**
 * @brief The InputDevice struct
 */
struct InputDevice {
  int states[InputState::Totalevents]{};
  int fire_ticks = 0;
  bool cached_tap = false;
  int ticks_since_tap = 0;
  unsigned char buttonmask{0x0};
  unsigned char directionmask{0x0};
};

/**
 * @brief The Gamepad struct
 */
struct Gamepad {
  InputDevice device;
  int sf_joystick_index = 0;
  float trigger_threshold = 0;
  float thumbstick_threshold = 50.0f;
};

/**
 * @brief The Keyboard struct
 */
struct Keyboard {
  InputDevice device;
};

// map entities to the device that controls them
// not a m ultimap means the same entity can be controlled by
// multiple input devices.
// change to a std::map for one to one relationship
inline std::multimap<Entity *, InputDevice *> controlled_entities;

// seems reasonable to have one global keyboard for our purposes
inline Keyboard keyboard;

/**
 * @brief handle_input
 * @param game
 * @param camera
 */
void handle_input(Game &game, Camera &camera);
/**
 * @brief update_controlled_entities
 */
void update_controlled_entities();
/**
 * @brief poll_controllers
 */
void poll_controllers();
