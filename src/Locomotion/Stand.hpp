#pragma once

#include "Locomotion.hpp"

/**
 * @brief The Stand locomotion sents the subject to a fixed location
 */
class Stand : public Locomotion {
public:
  /**
   * @brief Stand
   */
  Stand(Player &in_player);
  /**
   */
  ~Stand() override = default;
  /**
   * @brief init
   * @param in_target
   */
  void init();
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
};
