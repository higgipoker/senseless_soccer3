#include "Match.hpp"
//
#include "Ball/BallSprite.hpp"
#include "Team/Team.hpp"
//
#include <algorithm>

using namespace Engine;
//
int Match::instances = 0;
//
//
//
Match::Match(UniquePtr<Pitch> in_pitch, Team &in_home_team, Team &in_away_team, BallType in_ball_type)
    : pitch(std::move(in_pitch)), home_team(in_home_team), away_team(in_away_team) {
    auto ball_texture = std::make_unique<Engine::Texture>();
    ball_texture->loadFromFile(ball_factory.getSpriteSheeet(in_ball_type));

    if (factory.createMatchTexture(std::move(home_team.getSpriteTexture()), std::move(away_team.getSpriteTexture()),
                                   std::move(home_team.getShadowTexture()), std::move(away_team.getShadowTexture()),
                                   std::move(ball_texture))) {
        ball = std::make_unique<Ball>(std::move(std::make_unique<BallSprite>(factory.getMatchTexture())),
                                      std::move(std::make_unique<BallShadowSprite>(factory.getMatchTexture())));
        ball->getSprite().setPerspectivizable(true);
        ball->movable.name = "Ball";
    } else {
        std::cout << "create match texture failed" << std::endl;
    }

    home_team.setMatch(*this);
    away_team.setMatch(*this);

    home_team.setAttackingGoal(Engine::Direction::North);
    away_team.setAttackingGoal(Engine::Direction::South);

    home_team.gameplan.defensive_line_height = DefensiveLineType::Normal;
    away_team.gameplan.defensive_line_height = DefensiveLineType::Normal;

    home_team.gameplan.defensive_width_type = DefensivewidthType::Normal;
    away_team.gameplan.defensive_width_type = DefensivewidthType::Normal;

    ++instances;
    std::cout << instances << " matches" << std::endl;
}
//
//
//
Match::~Match(){
    --instances;
    std::cout << instances << " matches" << std::endl;
}
//
//
//
void Match::update() {
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
Ball &Match::getBall() {
    return *ball;
}
