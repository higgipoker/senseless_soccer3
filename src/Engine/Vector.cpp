
#include "Vector.hpp"

#include <cmath>

namespace Engine {
//
//
//
Vector3::Vector3(float xi, float yi) {
  x = xi;
  y = yi;
  z = 0;
}
//
//
//
float Vector3::operator[](Index idx) const {
  switch (idx) {
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
Vector3 &Vector3::operator+=(const Vector3 &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}
//
//
//
Vector3 &Vector3::operator-=(const Vector3 &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}
//
//
//
Vector3 &Vector3::operator*=(const Vector3 &rhs) {
  x *= rhs.x;
  y *= rhs.y;
  z *= rhs.z;
  return *this;
}
//
//
//
Vector3 &Vector3::operator*=(const float rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
  return *this;
}
//
//
//
Vector3 &Vector3::operator/=(const float rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;
  return *this;
}
//
//
//
Vector3 const Vector3::operator+(const Vector3 &rhs) const {
  return Vector3(*this) += rhs;
}
//
//
//
Vector3 const Vector3::operator-(const Vector3 &rhs) const {
  return Vector3(*this) -= rhs;
}
//
//
//
Vector3 const Vector3::operator*(const float rhs) const {
  return Vector3(*this) *= rhs;
}
//
//
//
Vector3 const Vector3::operator/(const float rhs) const {
  return Vector3(*this) /= rhs;
}
//
//
//
Vector3 const Vector3::operator^(Vector3 &v) {
  return Vector3(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
}
//
//
//
const Vector3 Vector3::operator+(const float scalar) {
  return Vector3(this->x + scalar, this->y + scalar, this->z + scalar);
}
//
//
//
const Vector3 Vector3::operator-(const float scalar) {
  return Vector3(this->x - scalar, this->y - scalar, this->z - scalar);
}
//
//
//
void Vector3::normalise() {
  if (Math::equal(this->magnitude(), 0)) return;

  float m = sqrtf(x * x + y * y + z * z);

  if (Math::less_than(m, 0)) {
    m = 1;
  }

  this->x /= m;
  this->y /= m;
  this->z /= m;

  if (Math::less_than(fabsf(this->x), 0)) {
    this->x = 0;
  }
  if (Math::less_than(fabsf(this->y), 0)) {
    this->y = 0;
  }
  if (Math::less_than(fabsf(this->z), 0)) {
    this->z = 0;
  }
}
//
//
//
void Vector3::normalise2d() {
  float m = sqrtf(x * x + y * y);

  if (Math::equal(m, 0)) {
    m = 1;
  }

  this->x /= m;
  this->y /= m;

  if (Math::less_than(fabsf(this->x), 0)) {
    this->x = 0;
  }
  if (Math::less_than(fabsf(this->y), 0)) {
    this->y = 0;
  }
  this->z = 0;
}
//
//
//
void Vector3::reflect(Vector3 &normal) {
  float dot = (x * normal.x) + (y * normal.y);
  dot *= 2;
  Vector3 reflected = normal * dot - *this;
  reflected.reverse();
  this->x = reflected.x;
  this->y = reflected.y;
  this->z = reflected.z;
}
//
//
//
float Vector3::projectionOn(Vector3 &line) {
  line.normalise();
  return dotProduct(line);
}
//
//
//
float Vector3::dotProduct(const Vector3 &rhs) {
  return (x * rhs.x + y * rhs.y + z * rhs.z);
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
void Vector3::rotate(float a, float x_origin, float y_origin) {
  a = Radians(a);

  this->x -= x_origin;
  this->y -= y_origin;

  float nx = cosf(a) * this->x - sinf(a) * this->y;
  float ny = sinf(a) * this->x + cosf(a) * this->y;

  this->x = nx;
  this->y = ny;

  this->x += x_origin;
  this->y += y_origin;
}
//
//
//
void Vector3::multiply(const Vector3 &rhs) {
  x *= rhs.x;
  y *= rhs.y;
  z *= rhs.z;
}
//
//
//
void Vector3::multiply2d(const float rhs) {
  x *= rhs;
  y *= rhs;
}
//
//
//
bool Vector3::equals(const Vector3 &v) {
  return Math::equal(x, v.x) && Math::equal(y, v.y) && Math::equal(z, v.z);
}
//
//
//
bool Vector3::equals(const Vector3 &v, float tolerance) {
  return (Math::equal(x, v.x, tolerance) && Math::equal(y, v.y, tolerance) &&
          Math::equal(z, v.z, tolerance));
}
//
//
//
void Vector3::roundAngle(int nearest_angle) {
  Vector3 rounded;
  float nearest_radians = Radians(static_cast<float>(nearest_angle));
  float angle = atan2f(y, x);
  float remainder = std::fmod(angle, nearest_radians);

  // if there is a remainder, do the rounding
  if (Math::greater_than(remainder, 0)) {
    float new_angle = roundf(angle / nearest_radians) * nearest_radians;
    this->x = cosf(new_angle);
    this->y = sinf(new_angle);
    if (Math::less_than(fabsf(this->x), 0)) {
      this->x = 0;
    }
    if (Math::less_than(fabsf(this->y), 0)) {
      this->y = 0;
    }
    if (Math::less_than(fabsf(this->z), 0)) {
      this->z = 0;
    }
  }

  // todo do we want to normalise here or leave that up to the caller?
  normalise();
}
//
//
//
float Vector3::perpProduct(const Vector3 &rhs, bool right_normal) {
  float y_component, x_component;

  if (right_normal) {
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
void Vector3::polar(float mag, float radians) {
  this->x = mag * cosf(radians);
  this->y = mag * sinf(radians);
  this->z = 0;
}
//
//
//
void Vector3::setMagnitude(float in_mag) {
  float mag = magnitude2d();
  x = x * in_mag / mag;
  y = y * in_mag / mag;
}
//
//
//
float Vector3::magnitude() const { return sqrtf(x * x + y * y + z * z); }
//
//
//
float Vector3::magnitude2d() const { return sqrtf(x * x + y * y); }
//
//
//
float Vector3::angle() const { return Degrees(atan2f(y, x)); }
//
//
//
void Vector3::unit(Vector3 v) {
  Vector3 unit = v / v.magnitude();
  x = unit.x;
  y = unit.y;
  z = unit.z;
}
//
//
//
float Vector3::magSquared() const { return magnitude() * magnitude(); }
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
void Vector3::reset() { x = y = z = 0; }
//
//
//
void Vector3::normalizeToUnits() {
  if (x > 0) {
    x = 1;
  } else if (x < 0) {
    x = -1;
  }

  if (y > 0) {
    y = 1;
  } else if (y < 0) {
    y = -1;
  }
}
//
//
//
bool Vector3::isMovingTowards(Vector3 testPoint, Vector3 objectVelocity) {
  Vector3 tmp{x, y};
  Vector3 toPoint = testPoint - tmp;
  float dot = toPoint.dotProduct(objectVelocity);
  return dot > 0;
}
//
//
//
void Vector3::fromSfVector(const sf::Vector2f &from) {
  this->x = from.x;
  this->y = from.y;
}
//
//
//
sf::Vector2f Vector3::toSfVector() const { return sf::Vector2f{x, y}; }
//
//
//
void Vector3::to2d() { this->z = 0; }

}  // namespace Engine
