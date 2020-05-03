#include "CoordinateSystem.h"
namespace Senseless {
//
//
//
void CoordinateSystem::init(const sf::FloatRect in_dimensions){

}
//
//
//
Vector3 CoordinateSystem::toScreenspace(const Vector3 &in_vector){
    Vector3 screenspace = in_vector;
    return screenspace;
}
//
//
//
Vector3 CoordinateSystem::fromScreenspace(const Vector3 &in_vector){
    Vector3 pitchspace = in_vector;
    return pitchspace;
}
}  // namespace Senseless
