#pragma once
#include <SFML/Graphics/Sprite.hpp>
namespace Data {
/**
 * @brief thin wrapper for sf::Sprite to make it sortable by z index,
 * and force informing the data pool when a z has changed (for sorting)
 */
struct SortableSprite : public sf::Sprite {
 public:
  /**
   * @brief get_z
   * @return
   */
  const int get_z() { return z; }

  /**
   * @brief set_z
   * @param _z
   */
  void set_z(const int _z) {
    if (z != _z) {
      z = _z;
      *sort_flag = true;
    }
  }

  /// for sorting
  static bool* sort_flag;
  int z = 0;
};

}  // namespace Data
