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
  void setBall(std::unique_ptr<Ball> in_ball);
  //
  //
  //
  Ball &getBall();
  //
  //
  //
 protected:
  /// match has a ball
  std::unique_ptr<Ball> ball;
};
