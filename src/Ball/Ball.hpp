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
    float radius = 3;

   // -----------------------------------------------------------------------
   // force all entities to be acquired through the factory
   // -----------------------------------------------------------------------
   protected:
    Ball (std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow);
   public:
    friend class EntityFactory;
};
// *
// *
// ***************************************************************************
}  // namespace Senseless
