#include "MiniMap.hpp"
namespace Senseless {
//
//
//
MiniMap::MiniMap() : Entity(std::make_unique<MiniMapSprite>(), std::make_unique<Sprite>()) {
}
}  // namespace Senseless
