#include "Team.hpp"
//
#include "Engine/Math.hpp"
#include "Match/Match.hpp"
//
#include <sstream>
//
Match *Team::match = nullptr;
//
//
//
Team::Team(const Kit &in_kit) : kit(in_kit) {
  sprite_texture.loadFromFile(player_factory.getSpriteSheeet(kit.type));
  sprite_texture.swapColors(kit.palette);

  shadow_texture.loadFromFile(player_factory.getShadowSheet());
}
//
//
//
Engine::Texture &Team::getSpriteTexture() { return sprite_texture; }
//
//
//
Engine::Texture &Team::getShadowTexture() { return shadow_texture; }
//
//
//
void Team::update() {
  set_key_players();

  for (auto &p : players) {
    p->update();
  }
}
//
//
//
void Team::addDefaultPlayers() {
  Player::connectMatch(*match);
  for (auto i = 0; i < 10; ++i) {
    UniquePtr<Player> player =
        player_factory.makePlayer(match->getMatchTexture());
    TeamData td;
    td.shirt_number = i + 1;
    player->setTeamData(td);
    player->movable.setPosition(
        match->getPitch().dimensions.center_spot.getCenter().x + (i * 10),
        match->getPitch().dimensions.center_spot.getCenter().y - 50);
    player->support_type = i;
    player->getBrain().changeState(brain_state::Support);
    std::stringstream ss;
    ss << "player" << i + 1;
    player->name = ss.str();
    addPlayer(std::move(player));
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
Player &Team::getPlayer() { return *players.back(); }
//
//
//
void Team::set_key_players() {
  if (!players.size()) return;

  // player in possession became null
  if (key_players.last_in_possession && !match->player_in_possession) {
    loose_ball_ticks = 60;
  }

  key_players.clear();

  // sort in order of closest to ball
  std::sort(players.begin(), players.end(),
            [](const auto &p1, const auto &p2) -> bool {
              return p1.get()->distance_from_ball <
                     p2.get()->distance_from_ball;
            });

  // closest player to ball
  auto it = players.begin();

  // but not the player in possession, or goalkeeper
  while (it->get() == match->player_in_possession) {
    ++it;
  }
  auto player = (*it).get();
  key_players.closest_to_ball = player;

  if (match->player_in_possession ||
      Engine::Math::greater_than(
          match->getBall().movable.velocity.magnitude2d(), 0)) {
    loose_ball_ticks = 60;
  } else if (--loose_ball_ticks == 0) {
    loose_ball_ticks = 60;
    Player *retriever = key_players.closest_to_ball;

    retriever->getBrain().changeState(brain_state::Retrieve);

    if (key_players.last_retriever) {
      key_players.last_retriever->getBrain().changeState(brain_state::Support);
    }
    key_players.last_retriever = retriever;
    std::cout << "retrieve loose ball" << std::endl;
  }

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
  key_players.last_in_possession = match->player_in_possession;
}
//
//
//
void Team::attachInputDevice(Engine::InputDevice &in_device) {
  input = &in_device;
}
//
//
//
Player &Team::getPlayer(const size_t in_which) {
  return *players.at(in_which).get();
}
