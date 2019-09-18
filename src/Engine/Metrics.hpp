#pragma once
#include "Vector.hpp"

namespace Engine {
namespace Metrics {
static const float cm_to_px = 0.2f;
//
// MetersToPixels
//
static int MetersToPixels(float meters) {
  return static_cast<int>(meters * 100 * cm_to_px);
}
//
//
//
static Vector3 MetersToPixels(const Vector3 &v) {
  return Vector3(MetersToPixels(v.x), MetersToPixels(v.y), MetersToPixels(v.z));
}
static const float CAMERA_HEIGHT = static_cast<float>(MetersToPixels(4.0f));
//
// these vals are depending on the gfx style and should be set from
// outside by the game
//
static const float CM_PER_PIXEL = 0.5f;
static const float Y_OFFSET_DUE_TO_HEIGHT = 7.6f;
}  // namespace Metrics
}  // namespace Engine
