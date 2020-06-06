#pragma once

#include <SFML/System/Vector2.hpp>

#include "Math.hpp"

namespace Senseless {

enum class Index { X = 0, Y = 1, Z = 2 };

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
    Vector3 ( void ) {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector3 ( const float xi, const float yi, const float zi ) {
        x = xi;
        y = yi;
        z = zi;
    }
    Vector3 ( const int xi, const int yi, const int zi ) {
        x = static_cast<float> ( xi );
        y = static_cast<float> ( yi );
        z = static_cast<float> ( zi );
    }
    Vector3 ( const float xi, const float yi ) {
        x = xi;
        y = yi;
        z = 0;
    }
    Vector3 ( const sf::Vector2f &_v ) {
        x = _v.x;
        y = _v.y;
        z = 0;
    }
    void reset();

    // -------------------------------------------------------------------------
    // scaler operators
    // -------------------------------------------------------------------------
    const Vector3 operator+ ( const float scalar );
    const Vector3 operator- ( const float scalar );

    // -------------------------------------------------------------------------
    // vector operators
    // -------------------------------------------------------------------------
    float         operator[] ( const Index idx ) const;
    Vector3 &     operator+= ( const Vector3 &rhs );
    Vector3 &     operator-= ( const Vector3 &rhs );
    Vector3 &     operator*= ( const Vector3 &rhs );
    Vector3 &     operator*= ( const float rhs );
    Vector3 &     operator/= ( const float rhs );
    const Vector3 operator+ ( const Vector3 &rhs ) const;
    const Vector3 operator- ( const Vector3 &rhs ) const;
    const Vector3 operator* ( const float rhs ) const;
    const Vector3 operator/ ( const float rhs ) const;
    const Vector3 operator^ ( const Vector3 &v );

    // -------------------------------------------------------------------------
    // vector operations
    // -------------------------------------------------------------------------
    void roundAngle ( const int nearest_angle );
    void normalise();
    void normalise2d();
    void reflect ( const Vector3 &normal );
    void perpendicular();
    void polar ( const float mag, const float radians );
    void setMagnitude ( const float in_mag );
    void unit ( const Senseless::Vector3& rhs );
    void reverse ( void );
    void normalizeToUnits();
    void rotate ( float a, const float x_origin = 0, const float y_origin = 0 );
    void multiply ( const Vector3 &rhs );
    void multiply2d ( const float rhs );
    inline void to2d() {
        z = 0;
    }

    // -------------------------------------------------------------------------
    // vector properties
    // -------------------------------------------------------------------------
    float magnitude ( void ) const;
    float magnitude2d ( void ) const;
    float magSquared ( void ) const;
    float angle ( void ) const;

    // -------------------------------------------------------------------------
    // other vector ops
    // -------------------------------------------------------------------------
    sf::Vector2f toSfVector() const;
    float        projectionOn ( Vector3 line );
    float        dotProduct ( const Vector3 &rhs );
    float        perpProduct ( const Vector3 &rhs, bool right_normal = true );
    bool         isMovingTowards ( const Vector3 testPoint, const Vector3 objectVelocity ) const;
    static bool  isMovingTowards ( const Vector3 pos, const Vector3 vel, const Vector3 test_point );

    // -------------------------------------------------------------------------
    // comparison operations
    // -------------------------------------------------------------------------
    bool equals ( const Vector3 &v );
    bool equals ( const Vector3 &v, float tolerance );

    // -------------------------------------------------------------------------
    // conversions
    // -------------------------------------------------------------------------
    void fromSfVector ( const sf::Vector2f &from );

    // -------------------------------------------------------------------------
    // static plain function style workers
    // -------------------------------------------------------------------------
    static inline Vector3 direction_to ( const Vector3& from, const Vector3& to, const bool in_2d = false ) {
        auto ret = to - from;
        if ( in_2d ) {
            ret.z = 0;
        }
        return ret;
    }
    static inline float distance_to ( const Vector3& from, const Vector3& to ) {
        return ( to - from ).magnitude();
    };
    static inline bool moving_towards ( const Vector3& position, const Vector3& velocity, const Vector3& testpoint ) {
        Vector3 toPoint = testpoint - position;
        return toPoint.dotProduct ( velocity ) > 0;
    }
    static inline float outerProduct(const Vector3& pos, const Vector3& dir, const Vector3& target){
        if ((pos.x - target.x) * dir.y> (pos.y- target.y) * dir.x){
            return 1;
        }
        return -1;
    }
};
}  // namespace Senseless
