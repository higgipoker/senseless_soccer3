#pragma once

#include "Locomotion.hpp"

#include "Engine/Movable.hpp"
/**
 * @brief The Pursue locomotion sents the subject to a fixed location
 */
class Pursue : public Locomotion {
 public:
  /**
   * @brief Pursue
   */
  Pursue(Player &in_player);
  /**
   */
  ~Pursue() override = default;
  /**
   * @brief init
   * @param in_target
   */
  void init(Engine::Movable &in_target);
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

 protected:
  Engine::Movable *target = nullptr;
  float last_distance = 0;
};
