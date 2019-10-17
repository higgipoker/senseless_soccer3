#pragma once

#include "Locomotion.hpp"

/**
 * @brief The Seek locomotion sents the subject to a fixed location
 */
class Seek : public Locomotion{
 public:
  /**
   * @brief Seek
   */
  Seek(Player & in_player);
  /**
    */
  ~Seek() override = default;
  /**
   * @brief init
   * @param in_target
   */
  void init(Engine::Vector3 in_target);
  /**
   * @brief start
   */
   void start() override;
  /**
   * @brief step
   */
   void step() override;
  /**
   * @brief end
   */
   void stop() override;
  /**
   * @brief fiished
   * @return
   */
   bool finished() override;

private:
   Engine::Vector3 target;
};
