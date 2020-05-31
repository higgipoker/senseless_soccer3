#include "BallFactory.hpp"
#include "Engine/BaseFactory.hpp"
namespace Senseless {
//
//
//
std::string BallFactory::getSpriteSheeet(const BallType in_ball_type) {
  switch (in_ball_type) {
    case BallType::Standard:
      return working_folder.getPath() + "/gfx/" + "ball.png";
      break;
  }
  return working_folder.getPath() + "/gfx/" + "ball.png";
}
}  // namespace Senseless
