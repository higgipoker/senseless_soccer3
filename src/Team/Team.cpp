#include "Team.hpp"
//
#include "PositionCenterBack.hpp"
#include "PositionCenterForward.hpp"
#include "PositionCenterMidfielder.hpp"
#include "PositionFullBack.hpp"
#include "PositionWideMidfielder.hpp"
//
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
#include "Engine/Math.hpp"
//
#include <cassert>
#include <sstream>
//
using namespace Engine;
//
//
//
int Team::instances = 0;
//
Team::Team(const std::string &in_name, const TeamType in_home_or_away, const Kit &in_kit)
    : name(in_name), home_or_away(in_home_or_away), kit(in_kit) {
    sprite_texture->loadFromFile(player_factory.getSpriteSheeet(kit.type));
    sprite_texture->swapColors(kit.palette);

    shadow_texture->loadFromFile(player_factory.getShadowSheet());

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
UniquePtr<Texture> Team::getSpriteTexture() {
    return std::move(sprite_texture);
}
//
//
//
UniquePtr<Texture> Team::getShadowTexture() {
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
    std::sort(std::begin(players), std::end(players), [](UniquePtr<Player> &p1, UniquePtr<Player> &p2) -> bool {
        return p1->distance_from_ball < p2->distance_from_ball;
    });
    if (!players.empty()) {
        if (auto player = players.at(0).get()) {
            closest_to_ball = player;
        }
    }

    for (auto &p : players) {
        p->update();
    }

    auto dist = (last_ball_position.magnitude2d() - match->getBall().movable.position.magnitude2d());
    if (Math::greater_than(fabs(dist), 50)) {
        gameplan.updateDefensiveLine(match->getPitch(), match->getBall(), attacking_goal);
        last_ball_position = match->getBall().movable.position;
    }

    defensive_line.setPosition(match->getPitch().toScreenSpace(gameplan.getDefensiveLine()).toSfVector());
    sprite.debug_shapes.clear();
    sprite.debug_shapes.push_back(&defensive_line);
}
//
//
//
void Team::addDefaultPlayers(const Team &in_other_team) {
    std::vector<UniquePtr<PlayingPosition>> positions;

    auto left_center_back = std::make_unique<PositionCenterBack>(match->getPitch(), *this, in_other_team);
    left_center_back->applyModifier(PositionModifier::Left);
    left_center_back->name = "Left Center Back";
    positions.emplace_back(std::move(left_center_back));

    auto right_center_back = std::make_unique<PositionCenterBack>(match->getPitch(), *this, in_other_team);
    right_center_back->applyModifier(PositionModifier::Right);
    right_center_back->name = "Right Center Back";
    positions.emplace_back(std::move(right_center_back));

    auto left_back = std::make_unique<PositionFullBack>(match->getPitch(), *this, in_other_team);
    left_back->applyModifier(PositionModifier::Left);
    left_back->name = "Letf Back";
    positions.emplace_back(std::move(left_back));

    auto right_back = std::make_unique<PositionFullBack>(match->getPitch(), *this, in_other_team);
    right_back->applyModifier(PositionModifier::Right);
    right_back->name = "Right Back";
    positions.emplace_back(std::move(right_back));

    auto left_center_mid = std::make_unique<PositionCenterMidfielder>(match->getPitch(), *this, in_other_team);
    left_center_mid->applyModifier(PositionModifier::Left);
    left_center_mid->name = "Left Center Mid";
    positions.emplace_back(std::move(left_center_mid));

    auto right_center_mid = std::make_unique<PositionCenterMidfielder>(match->getPitch(), *this, in_other_team);
    right_center_mid->applyModifier(PositionModifier::Right);
    right_center_mid->name = "Right Center Mid";
    positions.emplace_back(std::move(right_center_mid));

    auto left_midfielder = std::make_unique<PositionWideMidfielder>(match->getPitch(), *this, in_other_team);
    left_midfielder->applyModifier(PositionModifier::Left);
    left_midfielder->name = "Left Midfielder";
    positions.emplace_back(std::move(left_midfielder));

    auto right_midfielder = std::make_unique<PositionWideMidfielder>(match->getPitch(), *this, in_other_team);
    right_midfielder->applyModifier(PositionModifier::Right);
    right_midfielder->name = "Right Midfielder";
    positions.emplace_back(std::move(right_midfielder));

    auto left_center_forward = std::make_unique<PositionCenterForward>(match->getPitch(), *this, in_other_team);
    left_center_forward->applyModifier(PositionModifier::Left);
    left_center_forward->name = "Left Center Forward";
    positions.emplace_back(std::move(left_center_forward));

    auto right_center_forward = std::make_unique<PositionCenterForward>(match->getPitch(), *this, in_other_team);
    right_center_forward->applyModifier(PositionModifier::Right);
    right_center_forward->name = "Right Center Forward";
    positions.emplace_back(std::move(right_center_forward));

    for (size_t i = 0; i < positions.size(); ++i) {
        UniquePtr<Player> player = player_factory.makePlayer(*match, *this, in_other_team, home_or_away);
        TeamData td;
        td.shirt_number = static_cast<int>(i + 1);
        player->movable.name = positions[i]->name;
        player->setTeamData(td);
        player->support_type = static_cast<int>(i);
        player->setPlayingPosition(std::move(positions[i]));
        player->movable.position =
            match->getPitch().toScreenSpace({0, match->getPitch().getDimensions().halfway_line.getPosition().y});
        addPlayer(std::move(player));
    }
    positions.clear();
    goToSetPiecePositions(Situation::KickOff);
}
//
//
//
void Team::addPlayer(UniquePtr<Player> in_player) {
    players.push_back(std::move(in_player));
}
//
//
//
Player &Team::getPlayer(const size_t in_which) {
    assert(in_which < players.size());
    return *players.at(in_which).get();
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
