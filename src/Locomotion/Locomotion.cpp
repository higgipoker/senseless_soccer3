#include "Locomotion.hpp"

#include "Match/Match.hpp"
#include "Player/Player.hpp"
namespace Senseless {
//
//
//
Locomotion::Locomotion(Player& in_player) : player(in_player) {}
//
//
//
void Locomotion::stay_in_pitch() {
  // todo : now need to convert these to screen coords!

  //    auto pitchrect = player.match.getPitch().dimensions.bounds;

  //    const int buffer = 10;
  //    if (player.movable.position.x < pitchrect.getPosition().x + buffer) {
  //        player.movable.position.x = pitchrect.getPosition().x + buffer;
  //        player.movable.velocity.x = -player.movable.velocity.x;
  //    }
  //    if (player.movable.position.x > pitchrect.getPosition().x + pitchrect.getSize().x - buffer)
  //    {
  //        player.movable.position.x = pitchrect.getPosition().x + pitchrect.getSize().x - buffer;
  //        player.movable.velocity.x = -player.movable.velocity.x;
  //    }

  //    if (player.movable.position.y < pitchrect.getPosition().y + buffer) {
  //        player.movable.position.y = pitchrect.getPosition().y + buffer;
  //        player.movable.velocity.y = -player.movable.velocity.y;
  //    }
  //    if (player.movable.position.y > pitchrect.getPosition().y + pitchrect.getSize().y - buffer)
  //    {
  //        player.movable.position.y = pitchrect.getPosition().y + pitchrect.getSize().y - buffer;
  //        player.movable.velocity.y = -player.movable.velocity.y;
  //    }
}
}  // namespace Senseless
