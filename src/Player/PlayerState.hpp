#pragma once
#include <string>
namespace Senseless {
class Player;

/**
 * @brief The player_state enum
 */
enum class player_state { Stand, Run, Dribble };

// ***************************************************************************
// *                                                                         *
// * PlayerState                                                             *
// *                                                                         *
// ***************************************************************************
class PlayerState {
 public:
                PlayerState (Player &in_player);
  virtual       ~PlayerState();
  virtual void  start       () = 0;
  virtual void  step        ();
  virtual void  stop        () = 0;
  virtual bool  stateOver   () = 0;
  player_state  nextState   ();
  std::string   name = "Not Set";

 protected:
  Player&       player;
  player_state  next_state = player_state::Stand;
};
}  // namespace Senseless
