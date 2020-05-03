#pragma once
#include <string>
namespace Senseless {
enum class brain_state { Idle, Cover, Support, Retrieve, Dribble, Pass, Wait };

class Brain;
/**
 * @brief The BrainState class
 */
class BrainState {
 public:
  /**
   * @brief BrainState
   */
  BrainState(Brain &in_brain);
  /**
   * @brief ~BrainState
   */
  virtual ~BrainState();
  /**
   * @brief start
   */
  virtual void start() = 0;
  /**
   * @brief update
   */
  virtual void step() = 0;
  /**
   * @brief end
   */
  virtual void stop() = 0;
  /**
   * @brief stateOver
   * @return
   */
  virtual bool stateOver() = 0;
  /**
   * @brief changeToNextState
   */
  void changeToNextState();

  /// DEBUG
  std::string name;

 protected:
  /// sm context
  Brain &brain;

  /// next
  brain_state next_state = brain_state::Idle;
};

/**
 * @brief The BrainIdle class
 */
class BrainIdle : public BrainState {
 public:
  /**
   * @brief BrainState
   */
  BrainIdle(Brain &in_brain) : BrainState(in_brain) { name = "Idle"; }
  /**
   * @brief start
   */
  void start() override{};
  /**
   * @brief update
   */
  void step() override{};
  /**
   * @brief end
   */
  void stop() override{};
  /**
   * @brief stateOver
   * @return
   */
  bool stateOver() override { return false; };
};
}  // namespace Senseless
