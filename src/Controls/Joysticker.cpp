#include "Joysticker.hpp"

#include "Match/Match.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
void Joysticker::connectDevice(InputDevice &in_device) { input = &in_device; }
//
//
//
void Joysticker::update() {
  if (input && team) {
    if (player) {
      player->detachInput();
    }
    switch (state) {
      case JoystickerState::InPossession:
        player = team->match->player_in_possession;
        break;
      case JoystickerState::NotInPossession:
        player = team->key_players.closest_to_ball;
        break;
    }
    if (player) {
      player->attachInput(*input);
    }
    Player *p = team->key_players.pass_receiver
                    ? team->key_players.pass_receiver
                    : player;
    if (power_bar && p) {

      power_bar->setCenter(p->getSprite().getPosition().x,
                           p->getSprite().getPosition().y -
                               p->getSprite().getLocalBounds().height);
      power_bar->update();
    }
  }
}
//
//
//
void Joysticker::onInputEvent(const InputEvent in_event,
                              const std::vector<int> &in_params) {
  switch (in_event) {
    case InputEvent::FireDown:
      if (power_bar) {
        power_bar->start();
      }
      break;

    case InputEvent::FireUp: {
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
    } break;

    case InputEvent::DoubleTap:
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
      break;

    case InputEvent::SingleTap:
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
      break;
  }
}
