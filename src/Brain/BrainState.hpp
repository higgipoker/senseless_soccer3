#pragma once
#include <string>
namespace Senseless {
enum class brain_state : int{ Idle = 0, Cover, Support, Retrieve, Dribble, Pass, Wait };

class Brain;
class BrainState {
 public:
  BrainState(Brain &in_brain);
  virtual ~BrainState();
  virtual void start() = 0;
  virtual void step() = 0;
  virtual void stop() = 0;
  virtual bool stateOver() = 0;
  void changeToNextState();

  /// DEBUG
  std::string name;

 protected:
  /// sm context
  Brain &brain;

  /// next
  brain_state next_state = brain_state::Idle;
};
}  // namespace Senseless
