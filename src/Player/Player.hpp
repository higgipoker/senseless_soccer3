#pragma once
#include "PlayerSprite.hpp"
#include "PlayerStateDribble.hpp"
#include "PlayerStateRun.hpp"
#include "PlayerStateStand.hpp"
//
#include "Ball/Ball.hpp"
#include "Brain/Brain.hpp"
#include "Team/PlayingPosition.hpp"
//
#include "Engine/Controllable.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/TriangleShape.hpp"
#include "Engine/Types.hpp"

#include <SFML/Graphics/CircleShape.hpp>

#include <map>
//
//
//
class Match;
class Team;
//
//
//
struct TeamData {
    std::string shirt_name;
    int shirt_number = 0;
};
struct Attributes {};
enum class RunningSpeed { VerySlow, Slow, Normal, Fast, VeryFast };
//
//
//
inline std::map<RunningSpeed, float> run_speeds = {
    {RunningSpeed::VerySlow, 0.75F}, {RunningSpeed::Slow, 1.0F},     {RunningSpeed::Normal, 1.5F},
    {RunningSpeed::Fast, 2.0F},      {RunningSpeed::VeryFast, 2.5F},
};
//
//
//
inline std::map<RunningSpeed, float> dribble_speeds = {
    {RunningSpeed::VerySlow, 0.25F}, {RunningSpeed::Slow, 0.5F},     {RunningSpeed::Normal, 1.0F},
    {RunningSpeed::Fast, 1.5F},      {RunningSpeed::VeryFast, 2.0F},
};
//
//
//
inline std::map<RunningSpeed, float> kick_mods = {
    {RunningSpeed::VerySlow, 0.8F}, {RunningSpeed::Slow, 1.2F},     {RunningSpeed::Normal, 1.4F},
    {RunningSpeed::Fast, 2.1F},     {RunningSpeed::VeryFast, 3.0F},
};
//
//
//
class Player : public Engine::Entity, public Engine::Controllable {
   public:
    //
    //
    //
    Player(Match &in_match, const Team &in_my_team, const Team & in_other_team, UniquePtr<PlayerSprite> in_sprite, UniquePtr<PlayerSprite> in_shadow);
    //
    //
    //
    ~Player();
    //
    //
    //
    void update() override;
    //
    //
    //
    void handleInput() override;
    //
    //
    //
    void onInputEvent(const Engine::InputEvent in_event, const std::vector<int> &in_params) override;
    //
    //
    //
    void setTeamData(TeamData in_data);
    //
    //
    //
    void kick(const float in_force);
    //
    //
    //
    void shortPass(Player &in_receiver);
    //
    //
    //
    void run(Engine::Compass in_direction);
    //
    //
    //
    void run(Engine::Vector3 in_direction);
    //
    //
    //
    void stopRunning();
    //
    //
    //
    Engine::Compass getDirection();
    //
    //
    //
    Brain &getBrain();
    //
    //
    //
    bool ballInControlRange();
    //
    //
    //
    void goToSetPiecePosition(const Situation in_situation, const Engine::Direction in_pitch_side);
    //
    //
    //
    void setPlayingPosition(UniquePtr<PlayingPosition> in_position);
    // test
    Engine::ProgressBar *power_bar = nullptr;
    float distance_from_ball = 0;
    int support_type = 0;
    sf::TriangleShape short_pass_triangle;
    std::vector<Player *> short_pass_candidates;

   protected:
    //
    //
    //
    Match &match;
    const Team &my_team;
    const Team &other_team;
    Brain brain;
    bool ball_under_control = false;
    Engine::Compass facing;
    sf::CircleShape feet;
    sf::CircleShape control;
    PlayerStateStand state_stand;
    PlayerStateRun state_run;
    PlayerStateDribble state_dribble;
    PlayerState *state = nullptr;
    PlayerSprite &player_sprite;
    PlayerSprite &player_shadow;
    RunningSpeed speed = RunningSpeed::Normal;
    float current_speed = 0;
    TeamData team_data;
    Attributes attribs;
    UniquePtr<PlayingPosition> playing_position;
    //
    //
    //
    void face_ball();
    //
    //
    //
    void change_state(const player_state in_state);
    //
    //
    //
    void calc_short_pass_candidates();
    //
    //
    //
    void debug();

    static int instances;
   public:
    // state machine pattern
    friend class PlayerState;
    friend class PlayerStateStand;
    friend class PlayerStateRun;
    friend class PlayerStateDribble;
    friend class BrainDribble;
    friend class BrainRetrieve;
    friend class BrainSupport;
    friend class BrainCover;
    friend class Locomotion;
};
