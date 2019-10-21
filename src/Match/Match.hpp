#pragma once
#include "Ball/Ball.hpp"

#include "Engine/Types.hpp"
//
//
//

class Match {
 public:
  //
  //
  //
  Match();
  //
  //
  //
  void setBall(UnqPtr<Ball> in_ball);
  //
  //
  //
  Ball &getBall();
  //
  //
  //
 protected:
  /// match has a ball
  UnqPtr<Ball> ball;
};
