#pragma once
#include "Engine/BaseFactory.hpp"
#include "Engine/Texture.hpp"
//
//
//
namespace Senseless {
enum class BallType { Standard };

//
//
//
class BallFactory : public BaseFactory {
 public:
  //
  //
  //
  std::string getSpriteSheeet(const BallType in_ball_type) {
    switch (in_ball_type) {
      case BallType::Standard:
        return graphics_folder.getPath(true) + "ball.png";
        break;
    }

    return graphics_folder.getPath(true) + "ball.png";
  }

 private:
};

}  // namespace Senseless
