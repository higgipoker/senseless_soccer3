#pragma once

#include "Math.hpp"

#include <SFML/System/Vector2.hpp>

namespace Engine {

enum class Index { X = 0, Y = 1, Z = 2 };

//  ----------------------------------------------------------------------------
//
//  A class to represent a Vector
//
//
//  ----------------------------------------------------------------------------
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
  Vector3(void) {}
  Vector3(float xi, float yi, float zi) {
    x = xi;
    y = yi;
    z = zi;
  }
  Vector3(int xi, int yi, int zi) {
    x = static_cast<float>(xi);
    y = static_cast<float>(yi);
    z = static_cast<float>(zi);
  }
  Vector3(float xi, float yi);
  Vector3(const sf::Vector2f &_v) {
    x = _v.x;
    y = _v.y;
    z = 0;
  }
  void reset();

  // -------------------------------------------------------------------------
  // scaler operators
  // -------------------------------------------------------------------------
  const Vector3 operator+(const float scalar);
  const Vector3 operator-(const float scalar);

  // -------------------------------------------------------------------------
  // vector operators
  // -------------------------------------------------------------------------
  float operator[](Index idx) const;
  Vector3 &operator+=(const Vector3 &rhs);
  Vector3 &operator-=(const Vector3 &rhs);
  Vector3 &operator*=(const Vector3 &rhs);
  Vector3 &operator*=(const float rhs);
  Vector3 &operator/=(const float rhs);
  const Vector3 operator+(const Vector3 &rhs) const;
  const Vector3 operator-(const Vector3 &rhs) const;
  const Vector3 operator*(const float rhs) const;
  const Vector3 operator/(const float rhs) const;
  const Vector3 operator^(Vector3 &v);

  // -------------------------------------------------------------------------
  // vector operations
  // -------------------------------------------------------------------------
  void roundAngle(int nearest_angle);
  void normalise();
  void normalise2d();
  void reflect(Vector3 &normal);
  void perpendicular();
  void polar(float mag, float radians);
  void setMagnitude(float in_mag);
  void unit(Vector3 v);
  void reverse(void);
  void normalizeToUnits();
  void rotate(float a, float x_origin = 0, float y_origin = 0);
  void multiply(const Vector3 &rhs);
  void multiply2d(const float rhs);
  void to2d();

  // -------------------------------------------------------------------------
  // vector properties
  // -------------------------------------------------------------------------
  float magnitude(void) const;
  float magnitude2d(void) const;
  float magSquared(void) const;
  float angle(void) const;

  // -------------------------------------------------------------------------
  // other vector ops
  // -------------------------------------------------------------------------
  sf::Vector2f toSfVector();
  float projectionOn(Vector3 &line);
  float dotProduct(const Vector3 &rhs);
  float perpProduct(const Vector3 &rhs, bool right_normal = true);
  bool isMovingTowards(Vector3 testPoint, Vector3 objectVelocity);

  // -------------------------------------------------------------------------
  // comparison operations
  // -------------------------------------------------------------------------
  bool equals(const Vector3 &v);
  bool equals(const Vector3 &v, float tolerance);

  // -------------------------------------------------------------------------
  // conversions
  // -------------------------------------------------------------------------
  void fromSfVector(const sf::Vector2f &from);
};
}  // namespace Engine
