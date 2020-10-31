// #pragma once
// 
// #include "Engine/Vector.hpp"
// //
// #include <vector>
// namespace Senseless {
// //
// class MatchEngine;
// class Match;
// class Player;
// //
// //
// //
// enum class TeamID { Home, Away };
// //
// //
// //
// static inline void think(Player &player, const Match &match);
// //
// //
// //
// static inline void simulate(Player &player, const float dt);
// //
// //
// //
// enum class PlayerState { Standing, Running, Dribbling, Passing, Shooting, Tackling };
// //
// //
// //
// struct Player {
//     PlayerState state = PlayerState::Standing;
//     TeamID team = TeamID::Home;
//     unsigned int speed = 1;
//     unsigned int mass = 1;
//     Vector3 position;
//     Vector3 velocity;
//     Vector3 force;
// };
// //
// //
// //
// struct Team {
//     void update();
//     MatchEngine *match;
// };
// //
// //
// //
// enum class MatchState { PreGame, KickOff, Play, GoalKick, Corner, FreeKick, ThrowIn, HalfTime };
// //
// //
// //
// struct Match {
//     Team home_team;
//     Team away_team;
//     MatchState state = MatchState::PreGame;
// };
// //
// //
// //
// struct MatchEngine {
//     void start();
//     void update();
//     Match match;
//     std::vector<Player> players;
// };
// }  // namespace MatchEngine
