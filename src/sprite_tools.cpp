#include "sprite_tools.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void populate_frames(std::vector<sf::IntRect> &frames, int cols,
                            int width, int height, int start_row, int start_col, int frame_count) {
  int x = width*start_col;
  int y = height*start_row;
  int col = start_col;
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
