#include "Team.hpp"
//
#include "../Engine/EntityFactory.h"
//
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Game/Game.hpp"
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
Team::Team (const std::string &in_name)
    : Entity (std::make_unique<Sprite>(), std::make_unique<Sprite>()),
      name (in_name) {
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
void Team::update (const float in_dt) {
    // update players
    std::sort (std::begin (players),
               std::end (players),
    [] (Player * p1, Player * p2) -> bool {
        return p1->distance_from_ball < p2->distance_from_ball;
    });
    if (!players.empty()) {
        if (auto player = players.at (0)) {
            closest_to_ball = player;
        }
    }
    auto dist =
        (Vector::magnitude2d (last_ball_position) - Vector::magnitude2d (match->ball->movable.position));
    if (Math::greater_than (fabs (dist), 50)) {
        gameplan.updateDefensiveLine (*match->pitch, *match->ball, attacking_goal);
        last_ball_position = match->ball->movable.position;
    }

    defensive_line.setPosition (gameplan.getDefensiveLine().x, gameplan.getDefensiveLine().y);
    sprite.debug_shapes.clear();
    sprite.debug_shapes.push_back (&defensive_line);
    if (this->attacking_goal == Direction::South) {
        defensive_line.setFillColor (sf::Color::Blue);
        defensive_line.setOutlineColor (sf::Color::Blue);
    } else {
        defensive_line.setFillColor (sf::Color::Red);
        defensive_line.setOutlineColor (sf::Color::Red);
    }
}
//
//
//
void Team::addDefaultPlayers (Team &in_other_team) {
}
//
//
//
void Team::addPlayer (Player *in_player) {
    players.push_back (in_player);
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
std::vector<sf::Vector3f> Team::getPlayerPositions() {
    std::vector<sf::Vector3f> positions;
    for (auto &p : players) {
        positions.push_back ( (p->movable.position));
    }
    return positions;
}
//
//
//
void Team::goToSetPiecePositions (const Situation in_situation, const Direction in_pitch_side) {
    for (auto &player : players) {
        switch (in_situation) {
        case Situation::Corner:
        case Situation::KickOff:
        case Situation::ThrowIn:
        case Situation::FreeKick:
        case Situation::GoalKick:
            player->goToSetPiecePosition (in_situation, in_pitch_side);
            break;
        case Situation::Playing:
            if (attacking_state == AttackingState::Defending) {
                player->brain.changeState (brain_state::Cover);
            } else {
                player->brain.changeState (brain_state::Cover); // TODO
            }
            break;
        }
    }
}
//
//
//
void Team::setAttackingState (const AttackingState in_state) {
    attacking_state = in_state;
}
//
//
//
AttackingState Team::getAttackingState() const {
    return attacking_state;
}

}  // namespace Senseless
