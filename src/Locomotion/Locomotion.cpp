#include "Locomotion.hpp"

#include "Player/Player.hpp"
#include "Match/Match.hpp"
//
//
//
Locomotion::Locomotion(Player& in_player) : player(in_player) {}
//
//
//
void Locomotion::stay_in_pitch() {
  auto pitchrect = player.match->getPitch().dimensions.bounds;

  if(player.movable.position.x < pitchrect.getPosition().x){
    player.movable.velocity.x = -player.movable.velocity.x;
  }
  if(player.movable.position.x > pitchrect.getPosition().x + pitchrect.getSize().x){
    player.movable.velocity.x = -player.movable.velocity.x;
  }

  if(player.movable.position.y < pitchrect.getPosition().y){
    player.movable.velocity.y = -player.movable.velocity.y;
  }
  if(player.movable.position.y > pitchrect.getPosition().y + pitchrect.getSize().y){
    player.movable.velocity.y = -player.movable.velocity.y;
  }
}
