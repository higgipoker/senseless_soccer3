#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/Entity.hpp"
namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * Ball                                                                    *
// *                                                                         *
// ***************************************************************************
class Ball : public Entity {
    public:
     Ball (std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow);
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------        
    void  update          (const float in_dt) override;
    void  kick            (Vector3 in_force);
    void  applyTopSpin    (float in_factor);
    void  applyBackSpin   (float in_factor);
    void  applySideSpin   (Vector3 in_spin);

    // -----------------------------------------------------------------------
    // members
    // -----------------------------------------------------------------------
    Vector3           initial_position;
    Vector3           last_position;
    sf::CircleShape   collidable;
    bool              recording_distance = false;
    float             distance = 0;
    float             last_force = 0;
    protected:
    float radius = 2.5F;
};
// *
// *
// ***************************************************************************
}  // namespace Senseless
