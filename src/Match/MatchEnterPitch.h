#pragma once
#include "MatchState.h"
namespace Senseless {

    // ***************************************************************************
    // *                                                                         *
    // * Enter Pitch Match State                                                 *
    // *                                                                         *
    // ***************************************************************************
class MatchEnterPitch : public MatchState {
    public:
    MatchEnterPitch(Match &m);

    virtual void start      ()override;
    virtual void step       ()override;
    virtual void stop       ()override;
    virtual bool stateOver  ()override;
};
// *
// *
// ***************************************************************************

}  // namespace Senseless
