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
  void setBall(UniquePtr<Ball> in_ball);
  //
  //
  //
  Ball &getBall();
  //
  //
  //
 protected:
  /// match has a ball
  UniquePtr<Ball> ball;
};
