#pragma once
#include "PitchSprite.hpp"
#include "PitchTypes.hpp"
//
#include "Engine/Entity.hpp"
//
namespace Senseless {
class Pitch : public Entity {
 public:
  Pitch(const std::string &in_grass_texture);
  void update();
  Vector3 toScreenSpace(const Vector3 &in_vector) const;
  Vector3 toPitchSpace(const Vector3 &in_vector) const;
  const PitchDrawDimensions &getDimensions() const { return draw_dimensions; }  
  Vector3 getPointOfInterest(
      const PitchPointsOfInterest in_which,
      const PitchPointOfInterestSide in_side = PitchPointOfInterestSide::South) const;
  PitchDrawDimensions &getDrawDimensions(){return draw_dimensions;};

 private:
  PitchDrawDimensions draw_dimensions;
  PitchDimensions dimensions;  

  void init_bounds();
  void init_6_yard_boxes();
  void init_18_yard_boxes();
  void init_center_circle();
  void init_center_spot();
  void init_penalty_spots();
  void init_south_arc();
  void init_halfway_line();
};
}  // namespace Senseless
