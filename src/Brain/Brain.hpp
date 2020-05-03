// ---------------------------------------------------------------------------
//
// Brain
//
// ---------------------------------------------------------------------------
#pragma once

#include "BrainIdle.h"
#include "BrainCover.hpp"
#include "BrainDribble.hpp"
#include "BrainPass.hpp"
#include "BrainRetrieve.hpp"
#include "BrainState.hpp"
#include "BrainSupport.hpp"
#include "BrainWait.hpp"
#include "Locomotion/LocomotionManager.hpp"



namespace Senseless {
class Team;
class Match;
class Pitch;
class Player;
//
// Does the thinking for the player
//
class Brain {
 public:
  Brain (Player &in_player);

  void initEnvironment  (Match* in_match, Team* in_my_team, Team* in_other_team, Pitch* in_pitch);
  void think            ();
  void changeState      (const brain_state in_state);
  LocomotionManager     locomotion;

 protected:  
  Player&           player;
  BrainIdle         idle_state;
  BrainCover        cover_state;
  BrainRetrieve     retrieve_state;
  BrainDribble      dribble_state;
  BrainPass         pass_state;
  BrainSupport      support_state;
  BrainWait         wait_state;
  BrainState*       current_state = nullptr;

  struct{
      Match*    match       = nullptr;
      Team*     my_team     = nullptr;
      Team*     other_team  = nullptr;
      Pitch*    pitch       = nullptr;
  }env;

 public:
  // for sm pattern
  friend class BrainState;
  friend class BrainStateIdle;
  friend class BrainRetrieve;
  friend class BrainDribble;
  friend class BrainPass;
  friend class BrainSupport;
  friend class BrainCover;
  friend class BrainWait;

  // for diagnostics
  brain_state state = brain_state::Idle;
};
}  // namespace Senseless
