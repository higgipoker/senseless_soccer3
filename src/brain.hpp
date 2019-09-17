#pragma once
#include "player.hpp"

/**
 * @brief The BrainState enum
 */
enum class BrainState {
  Idle,
  Cover,
  Press,
  Tackle,
  Retrieve,
  Support,
  Dribble,
  Pass,
  Shoot
};

/**
 * @brief The brain struct
 */
struct Brain {
  BrainState state = BrainState::Cover;
};

// list of active brains
inline std::map<Player*, Brain*> brains;

/**
 * @brief update_brain
 * @param brain
 * @param player
 */
void update_brain(Brain &brain, Player &player);
/**
 * @brief change_brainstate
 * @param new_state
 */
void change_brainstate(BrainState new_state);
/**
 * @brief attach_brain
 * @param brain
 * @param player
 */
void attach_brain(Brain &brain, Player &player);
/**
 * @brief update_brains
 */
void update_brains();
