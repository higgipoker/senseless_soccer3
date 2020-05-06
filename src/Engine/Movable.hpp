#pragma once

#include "Vector.hpp"
//
#include <SFML/Graphics/Rect.hpp>
//
#include <string>

namespace Senseless {
//
//
//
class Movable {
   public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
    void            setPosition    (const float in_x, const float in_y, const float in_z);
    void            setPosition    (const float in_x, const float in_y);
    void            setPosition    (const sf::Vector2f in_point);
    void            move           (const float in_dx, const float in_dy);
    void            resetVelocity  ();
    void            place          (const Vector3& in_position);
    void            applyForce     (const Vector3& in_force);
    void            resetForces    ();
    void            step           (const float in_dt);
    void            toggleGravity  (const bool in_status);
    void            setBounds      (sf::FloatRect in_bounds);
    sf::FloatRect   getBounds      ();

    // -----------------------------------------------------------------------
    // members
    // -----------------------------------------------------------------------
    Vector3 position;
    Vector3 velocity;
    float speed = 1.F;
    struct Properties{
        float mass = 1;
        float co_bounciness = 0;
        float co_friction = 0;
        float co_air_resistance = 0;
        float co_spin_decay = 0.8F;
        float cross_section = 0;
    } properties;

    struct environment{
        float air_density = 1.0F;
    } environment;

    struct Forces{
        Vector3 sidespin;
        Vector3 topspin;
        Vector3 force;
        void reset() {
            force.reset();
        }
    } forces;

    bool is_hud = false;

    private:
    void integrate_improved_euler(const float in_dt);
    Vector3 integrate(const float in_dt);
    bool affected_by_gravity = true;
    sf::FloatRect bounds;
};
}  // namespace Senseless
