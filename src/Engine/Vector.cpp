
#include "Vector.hpp"

#include <cmath>

namespace Senseless {
//
//
//
float Vector3::operator[] ( Index idx ) const {
    switch ( idx ) {
    case Index::X:
        return x;
    case Index::Y:
        return y;
    case Index::Z:
        return z;
    }
    return 0;
}
//
//
//
Vector3 &Vector3::operator+= ( const Vector3 &rhs ) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
//
//
//
Vector3 &Vector3::operator-= ( const Vector3 &rhs ) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}
//
//
//
Vector3 &Vector3::operator*= ( const Vector3 &rhs ) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}
//
//
//
Vector3 &Vector3::operator*= ( const float rhs ) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}
//
//
//
Vector3 &Vector3::operator/= ( const float rhs ) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}
//
//
//
Vector3 const Vector3::operator+ ( const Vector3 &rhs ) const {
    return Vector3 ( *this ) += rhs;
}
//
//
//
Vector3 const Vector3::operator- ( const Vector3 &rhs ) const {
    return Vector3 ( *this ) -= rhs;
}
//
//
//
Vector3 const Vector3::operator* ( const float rhs ) const {
    return Vector3 ( *this ) *= rhs;
}
//
//
//
Vector3 const Vector3::operator/ ( const float rhs ) const {
    return Vector3 ( *this ) /= rhs;
}
//
//
//
Vector3 const Vector3::operator^ ( const Vector3 &rhs ) {
    return Vector3 ( y * rhs.z - z * rhs.y, -x * rhs.z + z * rhs.x, x * rhs.y - y * rhs.x );
}
//
//
//
const Vector3 Vector3::operator+ ( const float scalar ) {
    return Vector3 ( x + scalar, y + scalar, z + scalar );
}
//
//
//
const Vector3 Vector3::operator- ( const float scalar ) {
    return Vector3 ( x - scalar, y - scalar, z - scalar );
}
//
//
//
void Vector3::normalise() {
    if ( Math::equal ( magnitude(), 0 ) ) return;

    float m = sqrtf ( x * x + y * y + z * z );

    if ( Math::less_than ( m, 0 ) ) {
        m = 1;
    }

    x /= m;
    y /= m;
    z /= m;

    if ( Math::less_than ( fabsf ( x ), 0 ) ) {
        x = 0;
    }
    if ( Math::less_than ( fabsf ( y ), 0 ) ) {
        y = 0;
    }
    if ( Math::less_than ( fabsf ( z ), 0 ) ) {
        z = 0;
    }
}
//
//
//
void Vector3::normalise2d() {
    float m = sqrtf ( x * x + y * y );

    if ( Math::equal ( m, 0 ) ) {
        m = 1;
    }

    x /= m;
    y /= m;

    if ( Math::less_than ( fabsf ( x ), 0 ) ) {
        x = 0;
    }
    if ( Math::less_than ( fabsf ( y ), 0 ) ) {
        y = 0;
    }
    z = 0;
}
//
//
//
void Vector3::reflect ( const Vector3 &normal ) {
    float dot = ( x * normal.x ) + ( y * normal.y );
    dot *= 2;
    Vector3 reflected = normal * dot - *this;
    reflected.reverse();
    x = reflected.x;
    y = reflected.y;
    z = reflected.z;
}
//
//
//
float Vector3::projectionOn ( Vector3 line ) {
    line.normalise();
    return dotProduct ( line );
}
//
//
//
float Vector3::dotProduct ( const Vector3 &rhs ) {
    return ( x * rhs.x + y * rhs.y + z * rhs.z );
}
//
//
//
void Vector3::perpendicular() {
    float xtmp = x;
    x = y;
    y = -xtmp;
}
//
//
//
void Vector3::rotate ( float a, const float x_origin, const float y_origin ) {
    a = Radians ( a );

    x -= x_origin;
    y -= y_origin;

    float nx = cosf ( a ) * x - sinf ( a ) * y;
    float ny = sinf ( a ) * x + cosf ( a ) * y;

    x = nx;
    y = ny;

    x += x_origin;
    y += y_origin;
}
//
//
//
void Vector3::multiply ( const Vector3 &rhs ) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
}
//
//
//
void Vector3::multiply2d ( const float rhs ) {
    x *= rhs;
    y *= rhs;
}
//
//
//
bool Vector3::equals ( const Vector3 &v ) {
    return Math::equal ( x, v.x ) && Math::equal ( y, v.y ) && Math::equal ( z, v.z );
}
//
//
//
bool Vector3::equals ( const Vector3 &v, float tolerance ) {
    return ( Math::equal ( x, v.x, tolerance ) && Math::equal ( y, v.y, tolerance ) &&
             Math::equal ( z, v.z, tolerance ) );
}
//
//
//
void Vector3::roundAngle ( int nearest_angle ) {
    Vector3 rounded;
    float nearest_radians = Radians ( static_cast<float> ( nearest_angle ) );
    float angle = atan2f ( y, x );
    float remainder = std::fmod ( angle, nearest_radians );

    // if there is a remainder, do the rounding
    if ( Math::greater_than ( remainder, 0 ) ) {
        float new_angle = roundf ( angle / nearest_radians ) * nearest_radians;
        x = cosf ( new_angle );
        y = sinf ( new_angle );
        if ( Math::less_than ( fabsf ( x ), 0 ) ) {
            x = 0;
        }
        if ( Math::less_than ( fabsf ( y ), 0 ) ) {
            y = 0;
        }
        if ( Math::less_than ( fabsf ( z ), 0 ) ) {
            z = 0;
        }
    }

    // todo do we want to normalise here or leave that up to the caller?
    normalise();
}
//
//
//
float Vector3::perpProduct ( const Vector3 &rhs, bool right_normal ) {
    float y_component, x_component;

    if ( right_normal ) {
        x_component = y * rhs.x;
        y_component = -1 * x * rhs.y;
    } else {
        x_component = -1 * y * rhs.x;
        y_component = x * rhs.y;
    }
    return x_component + y_component;
}
//
//
//
void Vector3::polar ( float mag, float radians ) {
    x = mag * cosf ( radians );
    y = mag * sinf ( radians );
    z = 0;
}
//
//
//
void Vector3::setMagnitude ( float in_mag ) {
    float mag = magnitude2d();
    x = x * in_mag / mag;
    y = y * in_mag / mag;
}
//
//
//
float Vector3::magnitude() const {
    return sqrtf ( x * x + y * y + z * z );
}
//
//
//
float Vector3::magnitude2d() const {
    return sqrtf ( x * x + y * y );
}
//
//
//
float Vector3::angle() const {
    return Degrees ( atan2f ( y, x ) );
}
//
//
//
void Vector3::unit ( const Vector3& rhs ) {
    Vector3 unit = rhs / rhs.magnitude();
    x = unit.x;
    y = unit.y;
    z = unit.z;
}
//
//
//
float Vector3::magSquared() const {
    return magnitude() * magnitude();
}
//
//
//
void Vector3::reverse() {
    x = -x;
    y = -y;
    z = -z;
}
//
//
//
void Vector3::reset() {
    x = y = z = 0;
}
//
//
//
void Vector3::normalizeToUnits() {
    if ( x > 0 ) {
        x = 1;
    } else if ( x < 0 ) {
        x = -1;
    }

    if ( y > 0 ) {
        y = 1;
    } else if ( y < 0 ) {
        y = -1;
    }
}
//
//
//
bool Vector3::isMovingTowards ( Vector3 testPoint, Vector3 objectVelocity ) const {
    Vector3 tmp{x, y};
    Vector3 toPoint = testPoint - tmp;
    float dot = toPoint.dotProduct ( objectVelocity );
    return dot > 0;
}
//
//
//
bool Vector3::isMovingTowards ( const Vector3 pos, const Vector3 vel, const Vector3 test_point ) {
    Vector3 to_point = test_point - pos;
    float dot = to_point.dotProduct ( vel );
    return dot > 0;
}
//
//
//
void Vector3::fromSfVector ( const sf::Vector2f &from ) {
    x = from.x;
    y = from.y;
}
//
//
//
sf::Vector2f Vector3::toSfVector() const {
    return sf::Vector2f{x, y};
}

}  // namespace Senseless
