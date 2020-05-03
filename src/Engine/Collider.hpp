#pragma once
#include "Engine/TriangleShape.hpp"
#include "Engine/Vector.hpp"
//
#include <SFML/Graphics/CircleShape.hpp>
namespace Senseless {
//
//
//
class Collider {
   public:
    //
    //
    //
    static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
    //
    //
    //
    static bool contains(const sf::CircleShape &big, const sf::CircleShape &small);
    //
    //
    //
    static bool contains(const sf::CircleShape &circle, const Vector3 &point);
    //
    //
    //
    static bool collides(const Vector3 &point, const sf::TriangleShape &triangle);
    //
    //
    //
    template <class R, class P>
    static bool contains(R in_rect, P in_point) {
        if (in_point.x > in_rect.left && in_point.x < in_rect.left + in_rect.width && in_point.y > in_rect.top &&
            in_point.y < in_rect.top + in_rect.height) {
            return true;
        }
        return false;
    }
};
}  // namespace Senseless
