#pragma once
#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>
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
enum class Buttons {
  DPadUp = 0,
  DPadDown,
  DPadLeft,
  DPadRight,

  Button1,
  Button2,
  Button3,
  Button4,

  ShoulderLeft1,
  ShoulderLeft2,
  Shoulderright1,
  Shoulderright2,

  Start,
  Select
};
//
//
//
enum class InputEvent {
  FireDown = 0,
  FireUp,
  SingleTap,
  DoubleTap,

  Totalevents
};
//
//
//
class InputListener {
 public:
  //
  //
  //
  virtual ~InputListener() = default;
  //
  //
  //
  virtual void onEvent(const InputEvent in_event,
                       const std::vector<int> &in_params) = 0;
};

//
//
//
class InputDevice {
  //////////////////////////////////////////////////////////////////////
  /// Public Interface
  //////////////////////////////////////////////////////////////////////
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
  bool up();
  //
  //
  //
  bool down();
  //
  //
  //
  bool left();
  //
  //
  //
  bool right();
  //
  //
  //
  bool fire_down();
  //
  //
  //
  void setListener(InputListener &in_listener);

  //////////////////////////////////////////////////////////////////////
  /// Protected
  //////////////////////////////////////////////////////////////////////
 protected:
  std::map<InputEvent, int> events{
      {std::make_pair(InputEvent::FireDown, 0)},
      {std::make_pair(InputEvent::FireUp, 0)},
      {std::make_pair(InputEvent::SingleTap, 0)},
      {std::make_pair(InputEvent::DoubleTap, 0)}
  };
  struct {
    int FireLength = 0;
    int FireLengthCached = 0;
    int fire_ticks = 0;
    int ticks_since_tap = 0;
    bool cached_tap = false;

    const int fire_tap_length = 8;
    const int fire_double_tap_length = 12;
  } fire_params;
  unsigned char buttonmask{0x0};
  unsigned char directionmask{0x0};

  unsigned char old_buttonmask{0x00};
  //
  //
  //
  void resetStates();
  //
  //
  //
  void notify(const InputEvent in_event, const std::vector<int> &in_params);
  /// for now, only one listener per input device
  InputListener *listener = nullptr;
};

}  // namespace Engine
