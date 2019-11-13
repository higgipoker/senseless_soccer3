#include "Team.hpp"
//
#include "PositionCenterBack.hpp"
#include "PositionCenterMidfielder.hpp"
#include "PositionFullBack.hpp"
#include "PositionWideMidfielder.hpp"
#include "PositionCenterForward.hpp"
//
#include "Match/Match.hpp"
#include "Player/Player.hpp"
//
#include "Engine/Math.hpp"
//
#include <sstream>
//
using namespace Engine;
//
//
//
Team::Team(const TeamType in_home_or_away, const Kit &in_kit) : home_or_away(in_home_or_away), kit(in_kit) {
    sprite_texture->loadFromFile(player_factory.getSpriteSheeet(kit.type));
    sprite_texture->swapColors(kit.palette);

    shadow_texture->loadFromFile(player_factory.getShadowSheet());
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

    UniquePtr<PlayingPosition> left_center_back = std::make_unique<PositionCenterBack>();
    left_center_back->applyModifier(PositionModifier::Left);
    positions.emplace_back(std::move(left_center_back));

    UniquePtr<PlayingPosition> right_center_back = std::make_unique<PositionCenterBack>();
    right_center_back->applyModifier(PositionModifier::Right);
    positions.emplace_back(std::move(right_center_back));

    UniquePtr<PlayingPosition> left_back = std::make_unique<PositionFullBack>();
    left_back->applyModifier(PositionModifier::Left);
    positions.emplace_back(std::move(left_back));

    UniquePtr<PlayingPosition> right_back = std::make_unique<PositionFullBack>();
    right_back->applyModifier(PositionModifier::Right);
    positions.emplace_back(std::move(right_back));

    UniquePtr<PlayingPosition> left_center_mid = std::make_unique<PositionCenterMidfielder>();
    left_center_mid->applyModifier(PositionModifier::Left);
    positions.emplace_back(std::move(left_center_mid));

    UniquePtr<PlayingPosition> right_center_mid = std::make_unique<PositionCenterMidfielder>();
    right_center_mid->applyModifier(PositionModifier::Right);
    positions.emplace_back(std::move(right_center_mid));

    UniquePtr<PlayingPosition> left_midfielder = std::make_unique<PositionWideMidfielder>();
    left_midfielder->applyModifier(PositionModifier::Left);
    positions.emplace_back(std::move(left_midfielder));

    UniquePtr<PlayingPosition> right_midfielder = std::make_unique<PositionWideMidfielder>();
    right_midfielder->applyModifier(PositionModifier::Right);
    positions.emplace_back(std::move(right_midfielder));

    UniquePtr<PlayingPosition> left_center_forward = std::make_unique<PositionCenterForward>();
    left_center_forward->applyModifier(PositionModifier::Left);
    positions.emplace_back(std::move(left_center_forward));

    UniquePtr<PlayingPosition> right_mcenter_forward = std::make_unique<PositionCenterForward>();
    right_mcenter_forward->applyModifier(PositionModifier::Right);
    positions.emplace_back(std::move(right_mcenter_forward));

    for (auto i = 0; i < 10; ++i) {
        UniquePtr<Player> player = player_factory.makePlayer(*match, *this, in_other_team, home_or_away);
        TeamData td;
        td.shirt_number = i + 1;
        player->setTeamData(td);
        player->support_type = i;
        player->getBrain().changeState(brain_state::Support);
        std::stringstream ss;
        ss << "player" << i + 1;
        player->name = ss.str();
        player->movable.name = ss.str();
        player->movable.setPosition(match->getPitch().dimensions.center_spot.getCenter().x - 50 + (i * 10),
                                    match->getPitch().dimensions.center_spot.getCenter().y - 50);

        player->setPlayingPosition(std::move(positions[i]));
        player->getBrain().changeState(brain_state::Cover);

        addPlayer(std::move(player));
    }
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
Player &Team::getPlayer() {
    return *players.back();
}
//
//
//
Player &Team::getPlayer(const size_t in_which) {
    return *players.at(in_which).get();
}
//
//
//
void Team::setMatch(Match &in_match) {
    match = &in_match;

    // debugs
    defensive_line.setSize({match->getPitch().dimensions.bounds.getSize().x, 6});
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
