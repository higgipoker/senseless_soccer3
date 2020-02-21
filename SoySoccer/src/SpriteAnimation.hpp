#pragma once

#include <initializer_list>
#include <vector>
/**
 * @brief The SpriteAnimation class
 */
class SpriteAnimation {
 public:
  /**
   * @brief SpriteAnimation
   */
  SpriteAnimation(const int in_id, const int in_speed,
                  std::vector<int>  in_frames, bool in_loop = true);
  /**
   * @brief SpriteAnimation
   * @param in_args
   */
  SpriteAnimation(const int in_id, std::initializer_list<int> in_args);
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
  //
  //
  //
  int getID() const;
  //
  //
  //
  friend bool inline operator==(const SpriteAnimation& lhs,
                                const SpriteAnimation& rhs) {
    return lhs.id == rhs.id;
  }

 private:
  /// a unique identifier
  int id = -1;
  /// game frames per animation frame (speed)
  int frame_speed = 0;
  /// list of frame numbers
  std::vector<int> frames;
  /// loop the anim?
  bool loop = false;
  /// current frame
  std::vector<int>::iterator current_frame;
  /// count
  int count_frames = 0;
  /// for non looping anims, we can tell when they are finished
  bool finito = false;
};
