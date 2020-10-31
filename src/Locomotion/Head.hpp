#pragma once

#include "Locomotion.hpp"
namespace Senseless{
/**
 * @brief The Head locomotion sents the subject to a fixed location
 */
class Head : public Locomotion{
 public:
  /**
   * @brief Head
   */
  Head(Player & in_player);
  /**
    */
  ~Head() override = default;
  /**
   * @brief init
   * @param in_target
   */
  void init(sf::Vector3f in_direction);
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
   sf::Vector3f direction;
};
}
