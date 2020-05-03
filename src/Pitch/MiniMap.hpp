#pragma once
//
#include "Engine/Entity.hpp"
#include "MiniMapSprite.h"
//
namespace Senseless {
//
//
//
class MiniMap : public Entity {
 public:
  MiniMap();
  MiniMapSprite& getSprite() { return static_cast<MiniMapSprite&>(*sprite); }

 private:
};
}  // namespace Senseless
