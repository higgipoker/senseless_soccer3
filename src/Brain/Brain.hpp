#pragma once

#include "BrainCover.hpp"
#include "BrainDribble.hpp"
#include "BrainPass.hpp"
#include "BrainRetrieve.hpp"
#include "BrainState.hpp"
#include "BrainSupport.hpp"
#include "BrainWait.hpp"
#include "Locomotion/LocomotionManager.hpp"

namespace Senseless {
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

 protected:
  /// associated player
  Player &player;

  /// state machine
  BrainIdle idle_state;
  BrainCover cover_state;
  BrainRetrieve retrieve_state;
  BrainDribble dribble_state;
  BrainPass pass_state;
  BrainSupport support_state;
  BrainWait wait_state;
  BrainState *current_state = nullptr;

 public:
  // for sm pattern
  friend class BrainState;
  friend class BrainRetrieve;
  friend class BrainDribble;
  friend class BrainPass;
  friend class BrainSupport;
  friend class BrainCover;
  friend class BrainWait;
};
}  // namespace Senseless
