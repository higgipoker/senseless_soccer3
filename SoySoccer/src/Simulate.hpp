#pragma once
#include "Vector.hpp"
//
//
//
class Simulation {
   public:
    //
    //
    //
    void Simulate(float dt);
    //
    //
    //
    void ApplyForce(Vector3 force);
    int id = -1;
    float mass = 1;
    Vector3 position;
    Vector3 velocity;
    Vector3 force;
};
