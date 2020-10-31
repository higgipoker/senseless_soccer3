#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "Math.hpp"

namespace Senseless {
class Line;
enum class Index { X = 0, Y = 1, Z = 2 };

namespace Vector {
static void reset (sf::Vector3f& vec) {
    vec.x = vec.y = vec.z = 0;
}
static float magnitude (const sf::Vector3f& vec) {
    return sqrtf (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
static float magnitude2d (const sf::Vector3f& vec) {
    return sqrtf (vec.x * vec.x + vec.y * vec.y);
}
static void setMagnitude (sf::Vector3f& vec, const float in_mag) {
    float mag = magnitude2d (vec);
    vec.x = vec.x * in_mag / mag;
    vec.y = vec.y * in_mag / mag;
}
static void reverse (sf::Vector3f& vec) {
    vec.x = -vec.x;
    vec.y = -vec.y;
    vec.z = -vec.z;
}
static void normalise (sf::Vector3f& vec) {
    if (Math::equal (magnitude (vec), 0)) return;

    float m = sqrtf (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

    if (Math::less_than (m, 0)) {
        m = 1;
    }

    vec.x /= m;
    vec.y /= m;
    vec.z /= m;

    if (Math::less_than (fabsf (vec.x), 0)) {
        vec.x = 0;
    }
    if (Math::less_than (fabsf (vec.y), 0)) {
        vec.y = 0;
    }
    if (Math::less_than (fabsf (vec.z), 0)) {
        vec.z = 0;
    }
}
static void normalise2d (sf::Vector3f& vec) {
    float m = sqrtf (vec.x * vec.x + vec.y * vec.y);

    if (Math::equal (m, 0)) {
        m = 1;
    }

    vec.x /= m;
    vec.y /= m;

    if (Math::less_than (fabsf (vec.x), 0)) {
        vec.x = 0;
    }
    if (Math::less_than (fabsf (vec.y), 0)) {
        vec.y = 0;
    }
    vec.z = 0;
}
static void to2d (sf::Vector3f& vec) {
    vec.z = 0;
}
static float outerProduct (const sf::Vector3f& pos, const sf::Vector3f& dir, const sf::Vector3f& target) {
    if ( (pos.x - target.x) * dir.y > (pos.y - target.y) * dir.x) {
        return 1;
    }
    return -1;
}
static void roundToAngle (sf::Vector3f& vec, const float degrees) {
    sf::Vector3f rounded;
    float nearest_radians = Math::Radians (static_cast<float> (degrees));
    float angle = atan2f (vec.y, vec.x);
    float remainder = std::fmod (angle, nearest_radians);

    // if there is a remainder, do the rounding
    if (Math::greater_than (remainder, 0)) {
        float new_angle = roundf (angle / nearest_radians) * nearest_radians;
        vec.x = cosf (new_angle);
        vec.y = sinf (new_angle);
        if (Math::less_than (fabsf (vec.x), 0)) {
            vec.x = 0;
        }
        if (Math::less_than (fabsf (vec.y), 0)) {
            vec.y = 0;
        }
        if (Math::less_than (fabsf (vec.z), 0)) {
            vec.z = 0;
        }
    }

    // todo do we want to normalise here or leave that up to the caller?
    normalise (vec);
}
static void normaliseToUnits (sf::Vector3f vec) {
    if (vec.x > 0) {
        vec.x = 1;
    } else if (vec.x < 0) {
        vec.x = -1;
    }

    if (vec.y > 0) {
        vec.y = 1;
    } else if (vec.y < 0) {
        vec.y = -1;
    }
}
static void rotate (sf::Vector3f vec, const float angle, const float x_origin = 0, const float y_origin = 0) {
    const float a = Math::Radians (angle);

    vec.x -= x_origin;
    vec.y -= y_origin;

    float nx = cosf (a) * vec.x - sinf (a) * vec.y;
    float ny = sinf (a) * vec.x + cosf (a) * vec.y;

    vec.x = nx;
    vec.y = ny;

    vec.x += x_origin;
    vec.y += y_origin;
}
static float dotProduct (const sf::Vector3f& vec1, const sf::Vector3f& vec2) {
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
static bool isMovingTowards (const sf::Vector3f& vec, const sf::Vector3f& testPoint, const sf::Vector3f& objectVelocity) {
    sf::Vector3f tmp{vec.x, vec.y, 0.F};
    sf::Vector3f toPoint = testPoint - tmp;
    float dot = dotProduct (toPoint, objectVelocity);
    return dot > 0;
}
static float distanceTo (const sf::Vector3f& from, const sf::Vector3f& to) {
    return magnitude (to - from);
}
static sf::Vector3f directionTo (const sf::Vector3f& from, const sf::Vector3f& to, const bool in_2d = false) {
    auto ret = to - from;
    if (in_2d) {
        ret.z = 0;
    }
    return ret;
}
static void move2d (sf::Vector3f vec, const float dist) {
    vec.x += dist;
    vec.y += dist;
}
static void move2d (sf::Vector3f vec, const sf::Vector3f& dist) {
    vec.x += dist.x;
    vec.y += dist.y;
}

static float angle (const sf::Vector3f& vec) {
    return Math::Degrees (atan2f (vec.y, vec.x));
}

}// namespace Vector

/*
// ***************************************************************************
// *                                                                         *
// * Vector3                                                                 *
// *                                                                         *
// ***************************************************************************
class Vector3 {
public:
    // -------------------------------------------------------------------------
    // components
    // -------------------------------------------------------------------------
    float x = 0;
    float y = 0;
    float z = 0;

    // -------------------------------------------------------------------------
    // construct / destruct / setter
    // -------------------------------------------------------------------------
    Vector3 (void) {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector3 (const float xi, const float yi, const float zi) {
        x = xi;
        y = yi;
        z = zi;
    }
    Vector3 (const int xi, const int yi, const int zi) {
        x = static_cast<float> (xi);
        y = static_cast<float> (yi);
        z = static_cast<float> (zi);
    }
    Vector3 (const float xi, const float yi) {
        x = xi;
        y = yi;
        z = 0;
    }
    Vector3 (const sf::Vector2f &_v) {
        x = _v.x;
        y = _v.y;
        z = 0;
    }
    void reset() {
        x = y = z = 0;
    }

    // -------------------------------------------------------------------------
    // scaler operators
    // -------------------------------------------------------------------------
    const Vector3 operator+ (const float scalar);
    const Vector3 operator- (const float scalar);

    // -------------------------------------------------------------------------
    // vector operators
    // -------------------------------------------------------------------------
    float         operator[] (const Index idx) const;
    Vector3      &operator+= (const Vector3 &rhs);
    Vector3      &operator-= (const Vector3 &rhs);
    Vector3      &operator*= (const Vector3 &rhs);
    Vector3      &operator*= (const float rhs);
    Vector3      &operator/= (const float rhs);
    const Vector3 operator+ (const Vector3 &rhs) const;
    const Vector3 operator- (const Vector3 &rhs) const;
    const Vector3 operator* (const float rhs) const;
    const Vector3 operator/ (const float rhs) const;
    const Vector3 operator^ (const Vector3 &v);

    // -------------------------------------------------------------------------
    // mutating vector operations
    // -------------------------------------------------------------------------
    void roundAngle (const int nearest_angle);
    void normalise();
    void normalise2d();
    void reflect (const Vector3 &normal);
    void perpendicular();
    void polar (const float mag, const float radians);
    void setMagnitude (const float in_mag);
    void unit (const Senseless::Vector3 &rhs);
    void reverse (void);
    void normalizeToUnits();
    void rotate (float a, const float x_origin = 0, const float y_origin = 0);
    void multiply (const Vector3 &rhs);
    void multiply2d (const float rhs);
    void to2d() {
        z = 0;
    }

    // -------------------------------------------------------------------------
    // non mutating operations
    // -------------------------------------------------------------------------
    const Vector3 getRoundAngle (const int nearest_angle) {
        Vector3 tmp = *this;
        tmp.roundAngle (nearest_angle);
        return tmp;
    }
    const Vector3 getNormalised() {
        auto tmp = *this;
        tmp.normalise();
        return tmp;
    }
    const Vector3  getNormalise2d() {
        auto tmp = *this;
        tmp.normalise2d();
        return tmp;
    }
    const Vector3  getReflected (const Vector3 &normal) {
        auto tmp = *this;
        tmp.reflect (normal);
        return tmp;
    }
    const Vector3  getPerpendicular() {
        auto tmp = *this;
        tmp.perpendicular();
        return tmp;
    }
    const Vector3  getPolar (const float mag, const float radians) {
        auto tmp = *this;
        tmp.polar (mag, radians);
        return tmp;
    }
    const Vector3  getUnit (const Senseless::Vector3 &rhs) {
        auto tmp = *this;
        tmp.unit (rhs);
        return tmp;
    }
    const Vector3  getReverse (void) {
        auto tmp = *this;
        tmp.reverse();
        return tmp;
    }
    const Vector3  getNormalizeToUnits() {
        auto tmp = *this;
        tmp.normalizeToUnits();
        return tmp;
    }
    const Vector3  getRotated (float a, const float x_origin = 0, const float y_origin = 0) {
        auto tmp = *this;
        tmp.rotate (a, x_origin, y_origin);
        return tmp;
    }
    const Vector3  multipliedBy (const Vector3 &rhs) {
        auto tmp = *this;
        tmp.multiply (rhs);
        return tmp;
    }
    const Vector3  multipliedBy2d (const float rhs) {
        auto tmp = *this;
        tmp.multiply2d (rhs);
        return tmp;
    }
    const Vector3  getTo2d() {
        return {x, y, 0.F};
    }

    // -------------------------------------------------------------------------
    // vector properties
    // -------------------------------------------------------------------------
    float magnitude (void) const;
    float magnitude2d (void) const;
    float magSquared (void) const;
    float angle (void) const;

    // -------------------------------------------------------------------------
    // other vector ops
    // -------------------------------------------------------------------------
    sf::Vector2f toSfVector() const;
    float        projectionOn (Vector3 line);
    float        dotProduct (const Vector3 &rhs);
    float        perpProduct (const Vector3 &rhs, bool right_normal = true);
    bool         isMovingTowards (const Vector3 testPoint, const Vector3 objectVelocity) const;
    static bool  isMovingTowards (const Vector3 pos, const Vector3 vel, const Vector3 test_point);

    // -------------------------------------------------------------------------
    // comparison operations
    // -------------------------------------------------------------------------
    bool equals (const Vector3 &v);
    bool equals (const Vector3 &v, float tolerance);

    // -------------------------------------------------------------------------
    // conversions
    // -------------------------------------------------------------------------
    void fromSfVector (const sf::Vector2f &from);

    // -------------------------------------------------------------------------
    // static plain function style workers
    // -------------------------------------------------------------------------
    static Vector3 direction_to (const Vector3 &from, const Vector3 &to, const bool in_2d = false) {
        auto ret = to - from;
        if (in_2d) {
            ret.z = 0;
        }
        return ret;
    }
    static float distance_to (const Vector3 &from, const Vector3 &to) {
        return (to - from).magnitude();
    };
    static bool moving_towards (const Vector3 &position, const Vector3 &velocity, const Vector3 &testpoint) {
        Vector3 toPoint = testpoint - position;
        return toPoint.dotProduct (velocity) > 0;
    }
    static float outerProduct (const Vector3 &pos, const Vector3 &dir, const Vector3 &target) {
        if ( (pos.x - target.x) * dir.y > (pos.y - target.y) * dir.x) {
            return 1;
        }
        return -1;
    }
    float distanceToLine (const Line &in_line) const ;
};*/
}  // namespace Senseless
