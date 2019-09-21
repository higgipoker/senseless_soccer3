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
  Seek(Engine::Movable & in_entity, Engine::Movable & in_target);
  /**
    */
  ~Seek() override = default;
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
   bool fiished() override;
};
