#pragma once
#include "Vector.hpp"

namespace Senseless {

static const float cm_per_px = 0.2f;
static const float Z_PERSP_OFFSET = 0.5f;
static const float Y_OFFSET_DUE_TO_HEIGHT = 7.6f;
//
// MetersToPixels
//
static float MetersToPixels(float meters) {
  return static_cast<int>(meters * 100 * cm_per_px);
}
//
//
//
static Vector3 MetersToPixels(const Vector3 &v) {
  return Vector3(MetersToPixels(v.x), MetersToPixels(v.y), MetersToPixels(v.z));
}
static float CAMERA_HEIGHT = static_cast<float>(MetersToPixels(4.0f));


}  // namespace Senseless
