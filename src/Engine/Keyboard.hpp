#pragma once
#include "InputDevice.hpp"

#include <map>
//
//
//
namespace Engine {
//
//
//
inline std::map<InputState, sf::Keyboard::Key> keymap{
    {InputState::Up, sf::Keyboard::W},
    {InputState::Left, sf::Keyboard::A},
    {InputState::Down, sf::Keyboard::S},
    {InputState::Right, sf::Keyboard::D},
    {InputState::FireDown, sf::Keyboard::Up}};
//
//
//

class Keyboard : public InputDevice {
 public:
  //
  //
  //
  Keyboard() = default;
  //
  //
  //
  ~Keyboard() = default;
  //
  //
  //
  void update(const sf::Event &in_event) override;
  //
  //
  //
  bool up() override;
  //
  //
  //
  bool down() override;
  //
  //
  //
  bool left() override;
  //
  //
  //
  bool right() override;
};
}  // namespace Engine
