#include "sprite.hpp"
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void set_sprite_z(SortableSprite& sprite, float z) {
  if (sprite.z != z) {
    sprite.z = z;
    *SortableSprite::sort_flag = false;
  }
}
