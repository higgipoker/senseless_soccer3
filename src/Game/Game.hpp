#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Match/Match.hpp"

#include <set>
//
//
//
const sf::FloatRect world{0, 0, 2000, 3000};
/// maps distance <value> to force needed <key>
const static std::set<float> pass_distance = {80,  130, 180, 230, 280, 330,
                                 380, 430, 480, 530, 580};
//
//
//
