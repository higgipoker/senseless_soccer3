#include "Team.hpp"
//
#include "Match/Match.hpp"
Match* Team::match = nullptr;
//
//
//
Team::Team() {}
//
//
//
void Team::update() {
  set_key_players();

  for(auto &p : players){
    p->update();
  }
}
//
//
//
void Team::addPlayer(UniquePtr<Player> in_player) {
  in_player->my_team = this;
  players.push_back(std::move(in_player));
}
//
//
//
Player& Team::getPlayer() { return *players.back(); }
//
//
//
void Team::set_key_players() {
  if(!players.size())return;
  key_players.clear();

  // sort in order of closest to ball
  std::sort(
      players.begin(), players.end(), [](const auto &p1, const auto &p2) -> bool {
        return p1.get()->distance_from_ball < p2.get()->distance_from_ball;
      });

  // closest player to ball
  auto it = players.begin();
  auto player = (*it).get();

  // but not the player in possession, or goalkeeper
  while (player == match->player_in_possession) {
    ++it;
  }
  player = (*it).get();
  key_players.closest_to_ball = player;

  // ==================================================
  // pressers
  // ==================================================

  // ==================================================
  // pass candidates
  // ==================================================
  player = match->player_in_possession;
  if (player) {
    if (player->my_team == this) {
      for (it = players.begin(); it != players.end(); ++it) {
        if (it->get() == player) continue;

        { key_players.short_pass_candidates.push_back(it->get()); }
      }
    }
  }
}
