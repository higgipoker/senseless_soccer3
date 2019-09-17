#pragma once
namespace Engine{
/**
 * @brief The Movable class
 */
class Movable {
 public:
  /**
   * @brief Movable
   */
  Movable();
  /**
   * @brief step
   */
  void step(float _dt);
};
}
