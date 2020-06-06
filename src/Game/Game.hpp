#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <set>

#include "Match/Match.hpp"
#include "Pitch/MiniMap.hpp"
//
//
//
namespace Senseless {
const sf::IntRect            wnd_size{0, 0, 1280, 720};
const sf::FloatRect          world{0, 0, 1800, 2500};
const static std::set<float> pass_distance = {80, 130, 180, 230, 280, 330, 380, 430, 480, 530, 580};
//
//
//
struct Game {
    void init(Match &in_match, Team &in_home_team, Team &in_away_team, Ball &in_ball, Pitch &in_pitch, MiniMap &in_minimap) {
        match     = (&in_match);
        home_team = (&in_home_team);
        away_team = (&in_away_team);
        ball      = (&in_ball);
        pitch     = (&in_pitch);
        minimap   = (&in_minimap);
    }
    void reset() {
        match     = nullptr;
        home_team = nullptr;
        away_team = nullptr;
        ball      = nullptr;
        pitch     = nullptr;
        minimap   = nullptr;
    }
    Match *  match     = nullptr;
    Team *   home_team = nullptr;
    Team *   away_team = nullptr;
    Ball *   ball      = nullptr;
    Pitch *  pitch     = nullptr;
    MiniMap *minimap   = nullptr;
    //
    //
    //
    const char *pack() {
        return "test";
    }
};
}  // namespace Senseless
