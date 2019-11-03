#include "BrainSupport.hpp"

#include "Brain.hpp"

#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
BrainSupport::BrainSupport(Brain& in_brain) : BrainState(in_brain) {
  name = "Support";
}
//
//
//
void BrainSupport::start() {
  std::cout << "start " << name << std::endl;
  // tmp just run around randomly until we get too far from the player in
  // possession
  //change_direction();
  auto r = Compass::getRandomDirection();
  brain.player.run(r);
}
//
//
//
void BrainSupport::step() {
  // if no player is in possession, just freeze
  bool player_was_null = !player_in_possession;
  player_in_possession = brain.player.my_team->match->player_in_possession;
  if (!player_in_possession) {
    brain.locomotion.stand();
    return;
  }

  int CHANGE_TICKS = brain.player.support_type%2==0? 150:50;
  if(player_was_null && player_in_possession){
    ticks_since_change = CHANGE_TICKS;
  }

  auto pos = player_in_possession->movable.position.toSfVector();
  radius.setCenter(pos);
  radius.setRadius(300);

  auto dist = brain.player.distanceTo(*player_in_possession);
  if (dist > radius.getRadius()) {
    ticks_since_change = 0;
    Compass new_direction = brain.player.directionTo(*player_in_possession);
    brain.locomotion.head(new_direction.toVector());
  }

  else if (++ticks_since_change > CHANGE_TICKS) {
    ticks_since_change = 0;
    change_direction();
  }
}
//
//
//
void BrainSupport::stop() {std::cout << "stop " << name << std::endl;}
//
//
//
bool BrainSupport::stateOver() {
  if (brain.player.ballInControlRange()){
    next_state = brain_state::Dribble;
    return true;
  }
  return false;
}
//
//
//
void BrainSupport::change_direction() {
  Compass new_direction = Compass::getRandomDirection();
  while (new_direction == brain.player.getDirection()) {
    new_direction = Compass::getRandomDirection();
  }
  brain.locomotion.head(new_direction.toVector());
}
