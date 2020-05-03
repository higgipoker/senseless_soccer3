#pragma once
namespace Senseless {
class Match;

// ***************************************************************************
// *                                                                         *
// * Match State                                                             *
// *                                                                         *
// ***************************************************************************
class MatchState {
   public:
    MatchState(Match &m);

    virtual void start      ()=0;
    virtual void step       ()=0;
    virtual void stop       ()=0;
    virtual bool stateOver  ()=0;

   protected:
    Match &match;
};
// *
// *
// ***************************************************************************

}  // namespace Senseless
