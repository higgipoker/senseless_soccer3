#pragma once
#include "Ball/Ball.hpp"

#include "Engine/Sprite.hpp"
#include "Engine/Types.hpp"
#include "Pitch/Pitch.hpp"
#include "Team/Team.hpp"

#include <cassert>
//
//
//

class Match {
 public:
  //
  //
  //
  Match();
  //
  //
  //
  void update();
  //
  //
  //
  void setPitch(UniquePtr<Engine::Sprite> in_pitch);
  //
  //
  //
  void setBall(UniquePtr<Ball> in_ball);
  //
  //
  //
  Ball& getBall();
  //
  //
  //
  void addTeams(UniquePtr<Team> in_home_team, UniquePtr<Team> in_away_team);
  //
  //
  //
  inline Team& getHomeTeam() {
    assert(home_team.get());
    return *home_team;
  }
  //
  //
  //
  inline Team& getAwayTeam() {
    assert(away_team.get());
    return *away_team;
  }
  //
  //
  //
  inline Pitch& getPitch(){
    return static_cast<Pitch&>(*pitch.get());
  };
  Player* player_in_possession = nullptr;


 protected:
  UniquePtr<Engine::Sprite> pitch;
  UniquePtr<Ball> ball;
  UniquePtr<Team> home_team;
  UniquePtr<Team> away_team;
};
