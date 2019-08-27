#include "ball.hpp"

namespace Ball {

// -----------------------------------------------------------------------------
// populate_ball_sprite_frames
// -----------------------------------------------------------------------------
void populate_ball_sprite_frames(
    std::array<sf::IntRect, BALL_SPRITE_FRAMES> &frames) {
  int x = 0;
  int y = 0;
  int row = 0;
  int col = 0;
  for (auto &rect : frames) {
    rect.left = x;
    rect.top = y;
    rect.width = BALL_SPRITE_WIDTH;
    rect.height = BALL_SPRITE_HEIGHT;

    x += BALL_SPRITE_WIDTH;

    if (++col == BALL_SPRITESHEET_COLS) {
      x = 0;
      y += BALL_SPRITE_HEIGHT;
      col = 0;
    }
  }
}

}  // namespace Ball
