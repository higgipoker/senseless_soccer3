#pragma once

#include <SFML/System/Vector2.hpp>

#include <algorithm>
#include <cmath>

namespace Engine {
#define PI 3.14159265359f
#define RADIANS(a) a *(PI / 180.0f)
#define DEGREES(a) a *(180.0f / PI)

static const float TOL = 0.001f;
enum INDEX { X = 0, Y = 1, Z = 2 };

// maybe move this somewhere else
namespace Floats {

static bool equal(float a, float b, float epsilon = TOL) {
  return (std::fabs(a - b) <= epsilon);
}

static bool greater_than(float a, float b, float epsilon = TOL) {
  return (a - b) >
         ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) *
          epsilon);
}

static bool less_than(float a, float b, float epsilon = TOL) {
  return (b - a) >
         ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) *
          epsilon);
}

static bool abs_less_than(float a, float b, float epsilon = TOL) {
  return (b - std::fabs(a)) >
         ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) *
          epsilon);
}

}  // namespace Floats

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
  Vector3(float xi, float yi, float zi);
  Vector3(int xi, int yi, int zi);
  Vector3(float xi, float yi);
  void reset();

  // -------------------------------------------------------------------------
  // scaler operators
  // -------------------------------------------------------------------------
  const Vector3 operator+(const float scalar);
  const Vector3 operator-(const float scalar);

  // -------------------------------------------------------------------------
  // vector operators
  // -------------------------------------------------------------------------
  float operator[](INDEX idx) const;
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
  float operator*(Vector3 &rhs);

  // -------------------------------------------------------------------------
  // vector operations
  // -------------------------------------------------------------------------
  Vector3 roundAngle(int nearest_angle);
  Vector3 normalise();
  Vector3 normalise2d();
  Vector3 reflect(Vector3 &normal) const;
  Vector3 perpendicular();
  Vector3 polar(float mag, float radians);
  Vector3 setMagnitude(float mag);
  Vector3 unit(Vector3 v);
  Vector3 reverse(void);
  void normalizeToUnits();
  Vector3 rotate(float a, float x_origin = 0, float y_origin = 0) const;
  Vector3 multiply(const Vector3 &rhs) const;
  Vector3 multiply2d(const float rhs) const;

  // -------------------------------------------------------------------------
  // scaler operations
  // -------------------------------------------------------------------------
  float projectionOn(Vector3 line);
  float perpProduct(const Vector3 &v, bool right_normal = true);
  float magnitude(void) const;
  float magnitude2d(void);
  float magSquared(void);
  float dotProduct(const Vector3 &v) const;
  float angle(void);

  // -------------------------------------------------------------------------
  // comparison operations
  // -------------------------------------------------------------------------
  bool equals(const Vector3 &v);
  bool equals(const Vector3 &v, float tolerance);
  static bool isMovingTowards(Vector3 testPoint, Vector3 objectPosition,
                              Vector3 objectVelocity);

  // -------------------------------------------------------------------------
  // conversions
  // -------------------------------------------------------------------------
  static Vector3 fromSfVector(const sf::Vector2f &from);
};
}  // namespace Engine
