#pragma once

#include "PlayerTypes.hpp"
#include "PlayerSprite.hpp"
#include "PlayerStateDribble.hpp"
#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"
#include "Ball/Ball.hpp"
#include "Team/PlayingPosition.hpp"
#include "Brain/Brain.hpp"
#include "Engine/Controllable.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/TriangleShape.hpp"
#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <map>

namespace Senseless {
class Match;
class Team;
// ***************************************************************************
// *                                                                         *
// * Player                                                                  *
// *                                                                         *
// ***************************************************************************
class Player : public Entity, public Controllable {
 public:
  // -----------------------------------------------------------------------
  // functions
  // -----------------------------------------------------------------------
  Player (std::unique_ptr<PlayerSprite> in_sprite, std::unique_ptr<PlayerSprite> in_shadow);
            virtual ~Player                 ();
  void      update                  (const float in_dt) override;
  void      handleInput             () override;
  void      onInputEvent            (const InputEvent in_event, const std::vector<int> &in_params) override;
  void      setTeamData             (TeamData in_data);
  void      kick                    (const float in_force);
  void      shortPass               (Player &in_receiver);
  void      run                     (Compass in_direction);
  void      run                     (Vector3 in_direction);
  void      stopRunning             ();
  void      goToSetPiecePosition    (const Situation in_situation, const Direction in_pitch_side);
  void      setPlayingPosition      (std::unique_ptr<PlayingPosition> in_position);
  bool      ballInControlRange      ();
  Compass   getDirection            ();
  Brain&    getBrain                ();

  Team*                         my_team= nullptr;
  Team*                         other_team= nullptr;

 protected:
  // -----------------------------------------------------------------------
  // members
  // -----------------------------------------------------------------------
  PlayerStateStand              state_stand;
  PlayerStateRun                state_run;
  PlayerStateDribble            state_dribble;
  PlayerState*                  state = nullptr;  
  Brain                         brain;
  ProgressBar*                  power_bar = nullptr;
  sf::TriangleShape             short_pass_triangle;
  std::vector<Player*>          short_pass_candidates;    
  Compass                       facing;
  sf::CircleShape               feet;
  sf::CircleShape               control;      
  PlayerSprite&                 player_sprite;
  PlayerSprite&                 player_shadow;
  RunningSpeed                  speed = RunningSpeed::Normal;
  TeamData                      team_data;
  Attributes                    attribs;
  std::unique_ptr<PlayingPosition>    playing_position;
  float                         current_speed = 0;
  bool                          ball_under_control = false;
  float                         distance_from_ball = 0;
  int                           support_type = 0;
  // -----------------------------------------------------------------------
  // functions
  // -----------------------------------------------------------------------
  void face_ball                    ();
  void change_state                 (const player_state in_state);
  void calc_short_pass_candidates   ();
  void debug                        ();

  static int instances;

  // force entities to be acquired via factory

 public:
  friend class EntityFactory;
  // -----------------------------------------------------------------------
  // for state machine pattern
  // -----------------------------------------------------------------------
  friend class PlayerState;
  friend class PlayerStateStand;
  friend class PlayerStateRun;
  friend class PlayerStateDribble;
  friend class BrainDribble;
  friend class BrainRetrieve;
  friend class BrainSupport;
  friend class BrainCover;
  friend class BrainPass;
  friend class Locomotion;
  friend class Team;

  // for debug hud
  static std::map<brain_state, std::string > brainstates;
  brain_state getBrainState(){
      return brain.state;
  }
  void setBrainState(const brain_state in_state){
      brain.changeState(in_state);
  }
};
}  // namespace Senseless
