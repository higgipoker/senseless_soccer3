#pragma once

#include "PositionCenterBack.hpp"
#include "PositionCenterForward.hpp"
#include "PositionCenterMidfielder.hpp"
#include "PositionFullBack.hpp"
#include "PositionWideMidfielder.hpp"

#include "Pitch/Pitch.hpp"
#include "Team.hpp"

#include <memory>

namespace Senseless {
class PositionFactory {
   public:
    std::unique_ptr<PositionCenterBack> newCenterBack(const Pitch& in_pitch, const Team& in_myteam, const Team& in_otherteam) {
        auto pos = std::make_unique<PositionCenterBack>(in_pitch, in_myteam, in_otherteam);
        return pos; // giving ownership to caller
    }
    std::unique_ptr<PositionFullBack> newFullBack(const Pitch& in_pitch, const Team& in_myteam, const Team& in_otherteam) {
        auto pos = std::make_unique<PositionFullBack>(in_pitch, in_myteam, in_otherteam);
        return pos; // giving ownership to caller
    }
    std::unique_ptr<PositionCenterMidfielder> newCenterMidfielder(const Pitch& in_pitch, const Team& in_myteam, const Team& in_otherteam) {
        auto pos = std::make_unique<PositionCenterMidfielder>(in_pitch, in_myteam, in_otherteam);
        return pos; // giving ownership to caller
    }
    std::unique_ptr<PositionWideMidfielder> newWideMidfielder(const Pitch& in_pitch, const Team& in_myteam, const Team& in_otherteam) {
        auto pos = std::make_unique<PositionWideMidfielder>(in_pitch, in_myteam, in_otherteam);
        return pos; // giving ownership to caller
    }
    std::unique_ptr<PositionCenterForward> newCenterForward(const Pitch& in_pitch, const Team& in_myteam, const Team& in_otherteam) {
        auto pos = std::make_unique<PositionCenterForward>(in_pitch, in_myteam, in_otherteam);
        return pos; // giving ownership to caller
    }
};
}  // namespace Senseless
