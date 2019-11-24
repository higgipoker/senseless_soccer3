#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Match/Match.hpp"

#include <set>
//
//
//
const sf::FloatRect world{0, 0, 1800, 2500};
const static std::set<float> pass_distance = {80, 130, 180, 230, 280, 330, 380, 430, 480, 530, 580};
//
//
//
static struct GameState {
    Match *match = nullptr;
    Team *home_team = nullptr;
    Team *away_team = nullptr;
    Ball *ball = nullptr;
    Pitch *pitch = nullptr;
    //
    //
    //
    const char *pack() {
        return "test";
    }
    //
    //
    //
    GameState unpack(const char *packed) {
        GameState gamestate;
        return gamestate;
    }

} gamestate;
