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

};
}  // namespace Senseless
