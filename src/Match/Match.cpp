#include "Match.hpp"
//
#include "Ball/BallSprite.hpp"
#include "Team/Team.hpp"
//
#include <algorithm>

namespace Senseless {
//
int Match::instances = 0;
//
//
//
Match::Match(UniquePtr<Pitch> in_pitch,
             Team&            in_home_team,
             Team&            in_away_team,
             BallType         in_ball_type)
    : pitch(std::move(in_pitch)), home_team(in_home_team), away_team(in_away_team) {
    attacking_team    = TeamType::Home;
    auto ball_texture = std::make_unique<Texture>();
    ball_texture->loadFromFile(ball_factory.getSpriteSheeet(in_ball_type));

    if (factory.createMatchTexture(home_team.getSpriteTexture(),
                                   away_team.getSpriteTexture(),
                                   home_team.getShadowTexture(),
                                   away_team.getShadowTexture(),
                                   std::move(ball_texture))) {
        ball =
            std::make_unique<Ball>((std::make_unique<BallSprite>(factory.getMatchTexture())),
                                   (std::make_unique<BallShadowSprite>(factory.getMatchTexture())));
        ball->getSprite().setPerspectivizable(true);
        ball->name = "Ball";
    } else {
        std::cout << "create match texture failed" << std::endl;
    }

    home_team.setMatch(*this);
    away_team.setMatch(*this);

    home_team.setAttackingGoal(Direction::North);
    away_team.setAttackingGoal(Direction::South);

    home_team.gameplan.defensive_line_height = DefensiveLineType::Normal;
    away_team.gameplan.defensive_line_height = DefensiveLineType::Normal;

    home_team.gameplan.defensive_width_type = DefensivewidthType::Normal;
    away_team.gameplan.defensive_width_type = DefensivewidthType::Normal;

    home_team.setAttackingState(AttackingState::Attacking);
    away_team.setAttackingState(AttackingState::Defending);

    send(PlayerReachedKickoffPosition);

    ++instances;
    // std::cout << instances << " matches" << std::endl;
}
//
//
//
Match::~Match() {
    --instances;
    // std::cout << instances << " matches" << std::endl;
}
//
//
//
void Match::receive(const MessageName in_message) {
    switch (in_message) {
        case PlayerReachedKickoffPosition:
            break;
    }
}
//
//
//
const sf::Texture& Match::getMatchTexture() {
    return factory.getMatchTexture();
}
//
//
//
Team& Match::getHomeTeam() {
    return home_team;
}
//
//
//
Team& Match::getAwayTeam() {
    return away_team;
}
//
//
//
Pitch& Match::getPitch() const {
    return *pitch.get();
};
//
//
//
void Match::update() {
    pitch->update();
    ball->update();
    home_team.update();
    away_team.update();

    // keep the ball in the pitch
    auto pitchrect = pitch->getDimensions().bounds;

    if (ball->movable.position.x < pitchrect.getPosition().x) {
        ball->movable.velocity.x = -ball->movable.velocity.x;
    }
    if (ball->movable.position.x > pitchrect.getPosition().x + pitchrect.getSize().x) {
        ball->movable.velocity.x = -ball->movable.velocity.x;
    }

    if (ball->movable.position.y < pitchrect.getPosition().y) {
        ball->movable.velocity.y = -ball->movable.velocity.y;
    }
    if (ball->movable.position.y > pitchrect.getPosition().y + pitchrect.getSize().y) {
        ball->movable.velocity.y = -ball->movable.velocity.y;
    }
}
//
//
//
Ball& Match::getBall() {
    return *ball;
}
//
//
//
void Match::setAttackingTeam(const TeamType in_which) {
    attacking_team = in_which;
    switch (attacking_team) {
        case TeamType::Home:
            home_team.setAttackingState(AttackingState::Attacking);
            away_team.setAttackingState(AttackingState::Defending);
            break;
        case TeamType::Away:
            home_team.setAttackingState(AttackingState::Defending);
            away_team.setAttackingState(AttackingState::Attacking);
            break;
    }
}
}  // namespace Senseless
