#pragma once
#include "Ball/Ball.hpp"
/**
 * @brief The Match class
 */
class Match {
 public:
  //
  //
  //
  Match();
  //
  //
  //
  void setBall(Ball &in_ball);
  //
  //
  //
  Ball &getBall();
  //
  //
  //
 protected:
  /// match has a ball
  Ball *ball;
};
