#include "MiniMapSprite.h"
//
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
namespace Senseless {
MiniMapSprite::MiniMapSprite() {
    int i = 0;

    i = 0;
    for(auto &circle : players) {
        ++i;
        if(i < 10) {
            circle.setRadius(30);
            circle.setFillColor({255, 0, 0, 100});
        } else {
            circle.setRadius(30);
            circle.setFillColor({0, 0, 255, 100});
        }
    }
    ball.setRadius(15);
    ball.setFillColor(sf::Color::White);
    setPosition(10, 10);
    setScale(0.1F, 0.1F);
}
//
//
//
void MiniMapSprite::init(const PitchDrawShapes &in_dimensions) {
    // bounds
    // _
    bounds[0].position = {2, 0};
    bounds[1].position = {in_dimensions.bounds.getSize().x, 0};

    // |
    bounds[2].position = {in_dimensions.bounds.getSize().x, 0};
    bounds[3].position = {in_dimensions.bounds.getSize().x, in_dimensions.bounds.getSize().y};

    // _
    bounds[4].position = {in_dimensions.bounds.getSize().x, in_dimensions.bounds.getSize().y};
    bounds[5].position = {2, in_dimensions.bounds.getSize().y};

    // |
    bounds[6].position = {2, in_dimensions.bounds.getSize().y};
    bounds[7].position = {2, 0};

    {
        // north 6 box
        // |
        north_6_box[0] = {{in_dimensions.box_6.getPosition().x, in_dimensions.box_6.getPosition().y}};
        north_6_box[1] = {{in_dimensions.box_6.getPosition().x, in_dimensions.box_6.getPosition().y + in_dimensions.box_6.getSize().y}};

        // _
        north_6_box[2] = north_6_box[1];
        north_6_box[3] = {{north_6_box[1].position.x + in_dimensions.box_6.getSize().x, north_6_box[1].position.y}};

        // |
        north_6_box[4] = north_6_box[3];
        north_6_box[5] = {{north_6_box[3].position.x, north_6_box[0].position.y}};

        // south 6 yard box
        south_6_box[0] = north_6_box[0];
        south_6_box[1] = north_6_box[1];
        south_6_box[2] = north_6_box[2];
        south_6_box[3] = north_6_box[3];
        south_6_box[4] = north_6_box[4];
        south_6_box[5] = north_6_box[5];
        const float dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.box_6.getSize().y * 2);
        south_6_box[0].position.y += (dis_from_box_to_box + in_dimensions.box_6.getSize().y);
        south_6_box[1].position.y += (dis_from_box_to_box + in_dimensions.box_6.getSize().y);
        south_6_box[2].position.y += dis_from_box_to_box;
        south_6_box[3].position.y += dis_from_box_to_box;
        south_6_box[4].position.y += (dis_from_box_to_box + in_dimensions.box_6.getSize().y);
        south_6_box[5].position.y += (dis_from_box_to_box + in_dimensions.box_6.getSize().y);
    }

    {
        // north 18 box
        // |
        north_18_box[0] = {{in_dimensions.box_18.getPosition().x, in_dimensions.box_18.getPosition().y}};
        north_18_box[1] = {{in_dimensions.box_18.getPosition().x, in_dimensions.box_18.getPosition().y + in_dimensions.box_18.getSize().y}};

        // _
        north_18_box[2] = north_18_box[1];
        north_18_box[3] = {{north_18_box[1].position.x + in_dimensions.box_18.getSize().x, north_18_box[1].position.y}};

        // |
        north_18_box[4] = north_18_box[3];
        north_18_box[5] = {{north_18_box[3].position.x, north_18_box[0].position.y}};

        // south 18 yard box
        south_18_box[0] = north_18_box[0];
        south_18_box[1] = north_18_box[1];
        south_18_box[2] = north_18_box[2];
        south_18_box[3] = north_18_box[3];
        south_18_box[4] = north_18_box[4];
        south_18_box[5] = north_18_box[5];
        const float dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.box_18.getSize().y * 2);
        south_18_box[0].position.y += (dis_from_box_to_box + in_dimensions.box_18.getSize().y);
        south_18_box[1].position.y += (dis_from_box_to_box + in_dimensions.box_18.getSize().y);
        south_18_box[2].position.y += dis_from_box_to_box;
        south_18_box[3].position.y += dis_from_box_to_box;
        south_18_box[4].position.y += (dis_from_box_to_box + in_dimensions.box_18.getSize().y);
        south_18_box[5].position.y += (dis_from_box_to_box + in_dimensions.box_18.getSize().y);
    }

    halfwayline[0] = {{bounds[0].position.x, bounds[3].position.y / 2}};
    halfwayline[1] = {{bounds[1].position.x, bounds[3].position.y / 2}};

    // center circle
    center_circle = in_dimensions.center_circle;
    center_circle.setRadius(in_dimensions.center_circle.getRadius());
    center_circle.setCenter((in_dimensions.bounds.getSize().x) / 2, (in_dimensions.bounds.getSize().y) / 2);
    center_circle.setOutlineThickness(6);
    center_circle.setOutlineColor({255, 255, 255, 100});

    ////////////////////////////////////////////
    vlines = {// bounds
        bounds[0],
        bounds[1],
        bounds[2],
        bounds[3],
        bounds[4],
        bounds[5],
        bounds[6],
        bounds[7],

        // south 6 yard box
        south_6_box[0],
        south_6_box[1],
        south_6_box[2],
        south_6_box[3],
        south_6_box[4],
        south_6_box[5],

        // north 6 yard box
        north_6_box[0],
        north_6_box[1],
        north_6_box[2],
        north_6_box[3],
        north_6_box[4],
        north_6_box[5],

        // south 18 yard box
        south_18_box[0],
        south_18_box[1],
        south_18_box[2],
        south_18_box[3],
        south_18_box[4],
        south_18_box[5],

        // north 18 yard box
        north_18_box[0],
        north_18_box[1],
        north_18_box[2],
        north_18_box[3],
        north_18_box[4],
        north_18_box[5],

        // halfway line
        halfwayline[0],
        halfwayline[1]

    };
    for(auto &it : vlines) {
        it.color = {255, 255, 255, 100};
    }
}
//
//
//
void MiniMapSprite::update(const sf::Vector3f in_pitch_position, const std::vector<sf::Vector3f> &in_positions, const sf::Vector3f in_ball_position, const sf::RectangleShape in_camera) {
    size_t i = 0;
    for(auto &p : in_positions) {
        players[i].setCenter(p - in_pitch_position);
        ++i;
    }
    ball.setCenter(in_ball_position - in_pitch_position);
    camera = in_camera;
    camera.move(-in_pitch_position.x, -in_pitch_position.y);
}
//
//
//
sf::FloatRect MiniMapSprite::getGlobalBounds() const {
    return {getPosition().x, getPosition().y, bounds[1].position.x * getScale().x, bounds[3].position.y * getScale().y};
}
//
//
//
void MiniMapSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    {
        // background
        sf::RectangleShape bg;
        bg.setSize({getGlobalBounds().width, getGlobalBounds().height});
        bg.setFillColor({0, 0, 0, 100});
        bg.setOutlineThickness(0);
        sf::Transform transform;
        transform.translate(getPosition());
        states.transform = transform;
        target.draw(bg, transform);
    }

    {
        // lines
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        states.transform = transform;
        target.draw(vlines.data(), vlines.size(), sf::Lines, states);
    }

//     {
//         // center circle
//         sf::Transform transform;
//         transform.translate(getPosition());
//         transform.scale(getScale().x, getScale().x);
//         states.transform = transform;
//         target.draw(center_circle, states);
//     }

    {
        // ball
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        states.transform = transform;
        target.draw(ball, states);
    }

    {
        // players
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        states.transform = transform;
        for(size_t i = 0; i < players.size(); ++i) {
            target.draw(players.at(i), states);
        }
    }
    {
        // camera
        sf::RectangleShape cam = camera;
        cam.setFillColor({255, 255, 255, 20});
        cam.setOutlineColor(sf::Color::Black);
        cam.setOutlineThickness(12);
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        states.transform = transform;
        target.draw(cam, states);
    }
}
}  // namespace Senseless
