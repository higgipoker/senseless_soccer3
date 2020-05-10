#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace sf {
// ***************************************************************************
// *                                                                         *
// * TriangleShape                                                           *
// *                                                                         *
// ***************************************************************************
class TriangleShape : public Shape {
    public:
    explicit    TriangleShape   ();
    void        setPoints       (sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
    void        reset           ();
    std::size_t getPointCount   () const override { return 3; }
    Vector2f    getPoint        (std::size_t index) const override;

    private:
    Vector2f points[3];
};

}  // namespace sf
