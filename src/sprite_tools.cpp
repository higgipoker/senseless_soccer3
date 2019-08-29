#include "sprite_tools.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void populate_frames(std::vector<sf::IntRect> &frames, int cols,
                            int width, int height, int frame_count) {
  int x = 0;
  int y = 0;
  int col = 0;
  while (--frame_count >= 0) {
    sf::IntRect rect;
    rect.left = x;
    rect.top = y;
    rect.width = width;
    rect.height = height;
    frames.push_back(rect);

    x += width;

    if (++col == cols) {
      x = 0;
      y += height;
      col = 0;
    }
  }
}
