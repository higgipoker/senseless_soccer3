#pragma once
#include <gamelib3/compass/compass.hpp>

// map animations based onDirection
static std::map<gamelib3::Direction, std::string> standmap{
    std::make_pair(gamelib3::Direction::SOUTH_EAST, "stand_southeast"),
    std::make_pair(gamelib3::Direction::SOUTH, "stand_south"),
    std::make_pair(gamelib3::Direction::SOUTH_WEST, "stand_southwest"),
    std::make_pair(gamelib3::Direction::WEST, "stand_west"),
    std::make_pair(gamelib3::Direction::NORTH_WEST, "stand_northwest"),
    std::make_pair(gamelib3::Direction::NORTH, "stand_north"),
    std::make_pair(gamelib3::Direction::NORTH_EAST, "stand_northeast"),
    std::make_pair(gamelib3::Direction::EAST, "stand_east"),
};

static std::map<gamelib3::Direction, std::string> runmap{
    std::make_pair(gamelib3::Direction::SOUTH_EAST, "run_southeast"),
    std::make_pair(gamelib3::Direction::SOUTH, "run_south"),
    std::make_pair(gamelib3::Direction::SOUTH_WEST, "run_southwest"),
    std::make_pair(gamelib3::Direction::WEST, "run_west"),
    std::make_pair(gamelib3::Direction::NORTH_WEST, "run_northwest"),
    std::make_pair(gamelib3::Direction::NORTH, "run_north"),
    std::make_pair(gamelib3::Direction::NORTH_EAST, "run_northeast"),
    std::make_pair(gamelib3::Direction::EAST, "run_east"),
};
static std::map<gamelib3::Direction, std::string> slidemap{
    std::make_pair(gamelib3::Direction::SOUTH_EAST, "slide_southeast"),
    std::make_pair(gamelib3::Direction::SOUTH, "slide_south"),
    std::make_pair(gamelib3::Direction::SOUTH_WEST, "slide_southwest"),
    std::make_pair(gamelib3::Direction::WEST, "slide_west"),
    std::make_pair(gamelib3::Direction::NORTH_WEST, "slide_northwest"),
    std::make_pair(gamelib3::Direction::NORTH, "slide_north"),
    std::make_pair(gamelib3::Direction::NORTH_EAST, "slide_northeast"),
    std::make_pair(gamelib3::Direction::EAST, "slide_east"),
};
