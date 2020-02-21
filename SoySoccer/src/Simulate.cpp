#include "Simulate.hpp"

#include <iostream>
//
//
//
void Simulation::Simulate(float dt) {
    Vector3 acceleration = force / mass;
    velocity += acceleration * dt;
    position += velocity * dt;
    force.reset();
}
//
//
//
void Simulation::ApplyForce(Vector3 force) {
    this->force += force;
}
