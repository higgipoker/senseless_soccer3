#include "Team.hpp"
//
#include "Engine/Math.hpp"
#include "Match/Match.hpp"
//
#include <sstream>
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
UniquePtr<Engine::Texture> Team::getSpriteTexture() {
    return std::move(sprite_texture);
}
//
//
//
UniquePtr<Engine::Texture> Team::getShadowTexture() {
    return std::move(shadow_texture);
}
//
//
//
void Team::update() {
    // update players
    for (auto &p : players) {
        p->update();
    }
}
//
//
//
void Team::addDefaultPlayers() {
    for (auto i = 0; i < 10; ++i) {
        UniquePtr<Player> player = player_factory.makePlayer(*match, *this, home_or_away);
        TeamData td;
        td.shirt_number = i + 1;
        player->setTeamData(td);
        player->support_type = i;
        player->getBrain().changeState(brain_state::Support);
        std::stringstream ss;
        ss << "player" << i + 1;
        player->name = ss.str();
        player->movable.setPosition(match->getPitch().dimensions.center_spot.getCenter().x - 50 + (i * 10),
                                    match->getPitch().dimensions.center_spot.getCenter().y - 50);

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
}
