#include "Ball.hpp"
const int SHADOW_OFFSET_X = 4;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Ball::Ball() {
  movable = &ball_movable;
}
//
//
//
void Ball::update() {
  sprite->animate();

  shadow->setPosition(sprite->getPosition());
  shadow->move(SHADOW_OFFSET_X, SHADOW_OFFSET_Y);
}
