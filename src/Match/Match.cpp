#include "Match.hpp"
#include <algorithm>
#include "Ball/BallSprite.hpp"

using namespace Engine;
//
//
//
Match::Match(Team &in_home_team, Team &in_away_team, BallType in_ball_type)
    : home_team(in_home_team), away_team(in_away_team) {
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
}
//
//
//
void Match::update() {
    ball->update();
    home_team.update();
    away_team.update();

    // keep the ball in the pitch
    auto pitchrect = static_cast<Pitch *>(pitch.get())->dimensions.bounds;

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
void Match::setPitch(UniquePtr<Sprite> in_pitch) {
    pitch = std::move(in_pitch);
}
//
//
//
Ball &Match::getBall() {
    return *ball;
}
