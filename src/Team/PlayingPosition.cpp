#include "PlayingPosition.hpp"
//
//
//
void PlayingPosition::applyModifier(const PositionModifier in_mod) {
    switch (in_mod) {
        case PositionModifier::Center:
            modifier_mask |= modifier_center;
            break;
        case PositionModifier::Left:
            modifier_mask |= modifier_left;
            break;
        case PositionModifier::Right:
            modifier_mask |= modifier_right;
            break;
        case PositionModifier::Attacking:
            modifier_mask |= modifier_attacking;
            break;
        case PositionModifier::Defensive:
            modifier_mask |= modifier_defensive;
            break;
    }
}
