#include "Team.hpp"
//
#include "PositionCenterBack.hpp"
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

    defensive_line.setPosition(match->getPitch().dimensions.bounds.getPosition().x, gameplan.getDefensiveLine());
    sprite.debug_shapes.clear();
    sprite.debug_shapes.push_back(&defensive_line);
}
//
//
//
void Team::addDefaultPlayers() {
    for (auto i = 0; i < 1; ++i) {
        UniquePtr<Player> player = player_factory.makePlayer(*match, *this, home_or_away);
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

        // make a left center back
        UniquePtr<PlayingPosition> position = std::make_unique<PositionCenterBack>();
        position->applyModifier(PositionModifier::Right);
        player->setPlayingPosition(std::move(position));
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
