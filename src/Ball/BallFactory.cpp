#include "BallFactory.hpp"
#include "Engine/BaseFactory.hpp"
namespace Senseless {
//
//
//
std::string BallFactory::getSpriteSheeet(const BallType in_ball_type) {
  switch (in_ball_type) {
    case BallType::Standard:
      return graphics_folder.getPath(true) + "ball.png";
      break;
  }
  return graphics_folder.getPath(true) + "ball.png";
}
}  // namespace Senseless
