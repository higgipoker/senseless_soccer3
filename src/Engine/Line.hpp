#pragma once

#include "Vector.hpp"
namespace Senseless {

class Line {
public:
    float length() {
        return fabsf(p2.x - p1.x);
    }
    const Line operator+ ( const float scalar ){
        p1.x+=scalar;
        p1.y+=scalar;
        p2.x+=scalar;
        p2.y+=scalar;
        return *this;
    }
    const Line operator+ ( const sf::Vector3f& rhs){
        p1=p1+rhs;
        p2=p2+rhs;
        return *this;
    }
    
    sf::Vector3f p1, p2;
};

}
