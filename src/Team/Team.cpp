#include "Team.hpp"
//
#include "../Engine/EntityFactory.h"
//
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
#include "Engine/Math.hpp"
//
#include <cassert>
#include <sstream>
//
namespace Senseless {
//
//
//
int Team::instances = 0;
//
Team::Team(const std::string &in_name, const TeamStrip in_home_or_away, const Kit &in_kit)
    : name(in_name), home_or_away(in_home_or_away), kit(in_kit) {
    sprite_texture->loadFromFile(PlayerFactory::getSpriteSheeet(kit.type));
    sprite_texture->swapColors(kit.palette);
    shadow_texture->loadFromFile(PlayerFactory::getShadowSheet());

    ++instances;
    // std::cout << instances << " teams" << std::endl;
}
//
//
//
Team::~Team() {
    --instances;
    // std::cout << instances << " teams" << std::endl;
}
//
//
//
std::unique_ptr<Texture> Team::getSpriteTexture() {
    assert(sprite_texture != nullptr);
    return std::move(sprite_texture);
}
//
//
//
std::unique_ptr<Texture> Team::getShadowTexture() {
    assert(shadow_texture != nullptr);
    return std::move(shadow_texture);
}
//
//
//
void Team::setAttackingGoal(Direction in_dir) {
    attacking_goal = in_dir;
    if (attacking_goal == Direction::North) {
        defending_goal = Direction::South;
    } else {
        defending_goal = Direction::North;
    }
}
//
//
//
void Team::update() {
    // update players
    std::sort(std::begin(players),
              std::end(players),
              [](Player *p1, Player *p2) -> bool {
                  return p1->distance_from_ball < p2->distance_from_ball;
              });
    if (!players.empty()) {
        if (auto player = players.at(0)) {
            closest_to_ball = player;
        }
    }  
    auto dist =
        (last_ball_position.magnitude2d() - match->getBall().movable.position.magnitude2d());
    if (Math::greater_than(fabs(dist), 50)) {
        gameplan.updateDefensiveLine(match->getPitch(), match->getBall(), attacking_goal);
        last_ball_position = match->getBall().movable.position;
    }

    defensive_line.setPosition(
        match->getPitch().toScreenSpace(gameplan.getDefensiveLine()).toSfVector());
    sprite.debug_shapes.clear();
    sprite.debug_shapes.push_back(&defensive_line);
    if (this->attacking_goal == Direction::South) {
        defensive_line.setFillColor(sf::Color::Blue);
        defensive_line.setOutlineColor(sf::Color::Blue);
    } else {
        defensive_line.setFillColor(sf::Color::Red);
        defensive_line.setOutlineColor(sf::Color::Red);
    }
}
//
//
//
void Team::addDefaultPlayers(Team &in_other_team) {
}
//
//
//
void Team::addPlayer(Player* in_player) {
    players.push_back(in_player);
}
//
//
//
Player &Team::getPlayer(const size_t in_which) {
    assert(in_which < players.size());
    return *players.at(in_which);
}
//
//
//
void Team::setMatch(Match &in_match) {
    match = &in_match;

    // debugs
    defensive_line.setSize({match->getPitch().getDimensions().bounds.getSize().x, 6});
    defensive_line.setFillColor({255, 0, 0, 50});
}
//
//
//
Direction Team::getAttackingGoal() const {
    return attacking_goal;
}
//
//
//
Direction Team::getDefendingGoal() const {
    return defending_goal;
}
//
//
//
std::vector<Vector3> Team::getPlayerPositions() {
    std::vector<Vector3> positions;
    for (auto &p : players) {
        positions.push_back((p->movable.position - match->getPitch().getDimensions().origin));
    }
    return positions;
}
//
//
//
void Team::goToSetPiecePositions(const Situation in_situation, const Direction in_pitch_side) {
    for (auto &player : players) {
        switch (in_situation) {
            case Situation::Corner:
            case Situation::KickOff:
            case Situation::ThrowIn:
            case Situation::FreeKick:
            case Situation::GoalKick:
                player->goToSetPiecePosition(in_situation, in_pitch_side);
                break;
            case Situation::Playing:
                if (attacking_state == AttackingState::Defending) {
                    player->brain.changeState(brain_state::Cover);
                } else {
                    player->brain.changeState(brain_state::Cover);  // TODO
                }
                break;
        }
    }
}
//
//
//
void Team::setAttackingState(const AttackingState in_state) {
    attacking_state = in_state;
}
//
//
//
AttackingState Team::getAttackingState() const {
    return attacking_state;
}

}  // namespace Senseless
