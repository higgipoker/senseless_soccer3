#pragma once

#include "Vector.hpp"
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector3.hpp>
//
#include <string>

namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * Movable                                                                 *
// *                                                                         *
// ***************************************************************************
class Movable {
    public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
    void            setPosition    (const float in_x, const float in_y, const float in_z);
    void            setPosition    (const float in_x, const float in_y);
    void            setPosition    (const sf::Vector2f in_point);
    void            move           (const float in_dx, const float in_dy);
    void            place          (const sf::Vector3f& in_position);
    void            applyForce     (const sf::Vector3f& in_force);
    void            step           (const float in_dt);
    void            toggleGravity  (const bool in_status);
    void            setBounds      (sf::FloatRect in_bounds);
    void            resetForces    ();
    void            resetVelocity  ();
    sf::FloatRect   getBounds      ();

    // -----------------------------------------------------------------------
    // members
    // -----------------------------------------------------------------------
    sf::Vector3f position;
    sf::Vector3f velocity;
    float speed = 1.F;
    struct {
        float mass = 1;
        float co_bounciness = 0;
        float co_friction = 0;
        float co_air_resistance = 0;
        float co_spin_decay = 0.8F;
        float cross_section = 0;
    } properties;

    struct {
        float air_density = 1.0F;
    } environment;

    struct {
        sf::Vector3f sidespin;
        sf::Vector3f topspin;
        sf::Vector3f force;
        void reset() {
            Vector::reset(force);
        }
    }forces;

    bool is_hud = false;

    private:
    void integrate_improved_euler(const float in_dt);
    sf::Vector3f integrate(const float in_dt);
    bool affected_by_gravity = true;
    sf::FloatRect bounds;
};
}  // namespace Senseless
