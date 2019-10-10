#pragma once
#include <SFML/Window/Event.hpp>
//
//
//
namespace Engine {
//
//
//
constexpr unsigned char mask_zero{0};        // 0000 0001
constexpr unsigned char mask_a{1 << 0};      // 0000 0001
constexpr unsigned char mask_b{1 << 1};      // 0000 0010
constexpr unsigned char mask_x{1 << 2};      // 0000 0100
constexpr unsigned char mask_y{1 << 3};      // 0000 1000
constexpr unsigned char mask_l1{1 << 4};     // 0001 0000
constexpr unsigned char mask_r1{1 << 5};     // 0010 0000
constexpr unsigned char mask_back{1 << 6};   // 0100 0000
constexpr unsigned char mask_start{1 << 7};  // 1000 0000
//
//
//
constexpr unsigned char mask_dpad_up{1 << 0};      // 0000 0001
constexpr unsigned char mask_dpad_right{1 << 1};   // 0000 0010
constexpr unsigned char mask_dpad_down{1 << 2};    // 0000 0100
constexpr unsigned char mask_dpad_left{1 << 3};    // 0000 1000
constexpr unsigned char mask_stick_up{1 << 4};     // 0001 0000
constexpr unsigned char mask_stick_right{1 << 5};  // 0010 0000
constexpr unsigned char mask_stick_down{1 << 6};   // 0100 0000
constexpr unsigned char mask_stick_left{1 << 7};   // 1000 0000
//
//
//
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
class InputDevice {
 public:
  //
  //
  //
  InputDevice() = default;
  //
  //
  //
  virtual ~InputDevice() = default;
  //
  //
  //
  virtual void update(const sf::Event &in_event) = 0;
  //
  //
  //
  virtual bool up() = 0;
  //
  //
  //
  virtual bool down() = 0;
  //
  //
  //
  virtual bool left() = 0;
  //
  //
  //
  virtual bool right() = 0;

 protected:
  int states[InputState::Totalevents]{};
  unsigned char buttonmask{0x0};
  unsigned char directionmask{0x0};
};
}  // namespace Engine
