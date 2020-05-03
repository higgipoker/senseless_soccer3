#pragma once
#include "Engine/BaseFactory.hpp"
#include "Engine/Texture.hpp"
namespace Senseless {
enum class BallType { Standard };
class BallFactory : public BaseFactory {
 public:
  std::string getSpriteSheeet(const BallType in_ball_type);

 private:
};

}  // namespace Senseless
