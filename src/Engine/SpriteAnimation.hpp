#pragma once

#include <initializer_list>
#include <vector>

namespace Engine {
/**
 * @brief The SpriteAnimation class
 */
class SpriteAnimation {
 public:
  /**
   * @brief SpriteAnimation
   */
  SpriteAnimation(const int in_speed, const std::vector<int>& in_frames, bool in_loop = true);
  /**
   * @brief SpriteAnimation
   * @param in_args
   */
  SpriteAnimation(std::initializer_list<int> in_args);
  /**
   * @brief step
   */
  void step();
  /**
   * @brief finished
   * @return
   */
  bool finished();
  /**
   * @brief loop
   * @param in_yesorno
   */
  void setLoopable(bool in_yesorno);
  /**
   * @brief currentFrame
   * @return
   */
  int currentFrame();

 private:
  /// list of frame numbers
  std::vector<int> frames;
  /// current frame
  std::vector<int>::iterator current_frame;
  /// game frames per animation frame (speed)
  int frame_speed = 0;
  /// count
  int count_frames = 0;
  /// loop the anim?
  bool loop = false;
  /// for non looping anims, we can tell when they are finished
  bool finito = false;
};
}  // namespace Engine
