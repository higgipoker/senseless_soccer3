#pragma once

#include "BrainState.hpp"
#include "BrainRetrieve.hpp"
#include "BrainDribble.hpp"
#include "Locomotion/LocomotionManager.hpp"

class Player;

/**
 * @brief The Brain class
 */
class Brain {
 public:
  /**
   * @brief Brain
   */
  Brain(Player &in_player);
  /**
   * @brief update
   */
  void update();
  /**
   * @brief changeState
   */
  void changeState(const brain_state in_state);

  /// brain controls movement
  LocomotionManager locomotion;

  // tmp
  void activate(){
    changeState(brain_state::Dribble);
  };

 protected:
  /// associated player
  Player &player;

  /// state machine
  BrainIdle idle_state;
  BrainRetrieve retrieve_state;
  BrainDribble dribble_state;
  BrainState *current_state = nullptr;


 public:
  // for sm pattern
  friend class BrainState;
  friend class BrainRetrieve;
  friend class BrainDribble;
};
