#pragma once

#include "Locomotion.hpp"

/**
 * @brief The Pursue locomotion sents the subject to a fixed location
 */
class Pursue : public Locomotion{
 public:
  /**
   * @brief Pursue
   */
  Pursue(Engine::Movable & in_movable);
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
};

class PursueTilCaught : public Pursue{
public:
  /**
   * @brief PursueTilCaught
   * @param in_movable
   */
  PursueTilCaught(Engine::Movable & in_movable, float in_range = 1);
  /**
   * @brief fiished
   * @return
   */
   bool finished() override;
   /**
    * @brief init
    * @param in_target
    */
   void init(Engine::Movable &in_target,float in_range = 20);
protected:
   float range = 0;
};
