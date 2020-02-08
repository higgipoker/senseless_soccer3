#include "MiniMap.hpp"
//
//
//
MiniMap::MiniMap() {
    for (size_t i = 0; i < 20; ++i) {
        players[i].position = {0, 0};
        if (i < 10) {
            players[i].color = sf::Color::Red;
            circles[i].setRadius(30);
            circles[i].setFillColor({255, 0, 0, 100});
        } else {
            players[i].color = sf::Color::Blue;
            circles[i].setRadius(30);
            circles[i].setFillColor({0, 0, 255, 100});
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
void MiniMap::updatePlayerPositions(const std::vector<Engine::Vector3>& in_positions,
                                    const Engine::Vector3 in_ball_position) {
    size_t i = 0;
    for (auto& p : in_positions) {
        players[i].position = p.toSfVector();
        circles[i].setCenter(p.toSfVector());
        ++i;
    }
    ball.setCenter(in_ball_position.toSfVector());
}
//
//
//
void MiniMap::init(const sf::FloatRect in_bounds, const PitchDrawDimensions& in_dimensions,
                   const std::string& in_grass_texture) {
    // make a texture for drawing the lines on
    pitch_texture.create(static_cast<int>(in_dimensions.bounds.getSize().x * getScale().x + 4),
                         static_cast<int>(in_dimensions.bounds.getSize().y * getScale().x + 4));

    sprite.setTexture(pitch_texture.getTexture(), true);

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
        // south 6 box
        // |
        south_6_box[0] = {{in_dimensions.south_6.getPosition().x,
                           in_dimensions.south_6.getPosition().y + in_dimensions.south_6.getSize().y}};
        south_6_box[1] = {{in_dimensions.south_6.getPosition().x, in_dimensions.south_6.getPosition().y}};

        // _
        south_6_box[2] = south_6_box[1];
        south_6_box[3] = {{south_6_box[1].position.x + in_dimensions.south_6.getSize().x, south_6_box[1].position.y}};

        // |
        south_6_box[4] = south_6_box[3];
        south_6_box[5] = {{south_6_box[3].position.x, south_6_box[0].position.y}};

        north_6_box[0] = south_6_box[0];
        north_6_box[1] = south_6_box[1];
        north_6_box[2] = south_6_box[2];
        north_6_box[3] = south_6_box[3];
        north_6_box[4] = south_6_box[4];
        north_6_box[5] = south_6_box[5];

        const float dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.south_6.getSize().y * 2);

        north_6_box[0].position.y -= (dis_from_box_to_box + in_dimensions.south_6.getSize().y);
        north_6_box[1].position.y -= (dis_from_box_to_box + in_dimensions.south_6.getSize().y);
        north_6_box[2].position.y -= dis_from_box_to_box;
        north_6_box[3].position.y -= dis_from_box_to_box;
        north_6_box[4].position.y -= (dis_from_box_to_box + in_dimensions.south_6.getSize().y);
        north_6_box[5].position.y -= (dis_from_box_to_box + in_dimensions.south_6.getSize().y);
    }

    {
        // south 18 box
        // |
        south_18_box[0] = {{in_dimensions.south_18.getPosition().x,
                            in_dimensions.south_18.getPosition().y + in_dimensions.south_18.getSize().y}};
        south_18_box[1] = {{in_dimensions.south_18.getPosition().x, in_dimensions.south_18.getPosition().y}};

        //    // _
        south_18_box[2] = south_18_box[1];
        south_18_box[3] = {
            {south_18_box[1].position.x + in_dimensions.south_18.getSize().x, south_18_box[1].position.y}};

        //    // |
        south_18_box[4] = south_18_box[3];
        south_18_box[5] = {{south_18_box[3].position.x, south_18_box[0].position.y}};

        north_18_box[0] = south_18_box[0];
        north_18_box[1] = south_18_box[1];
        north_18_box[2] = south_18_box[2];
        north_18_box[3] = south_18_box[3];
        north_18_box[4] = south_18_box[4];
        north_18_box[5] = south_18_box[5];

        const float dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.south_18.getSize().y * 2);

        north_18_box[0].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
        north_18_box[1].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
        north_18_box[2].position.y -= dis_from_box_to_box;
        north_18_box[3].position.y -= dis_from_box_to_box;
        north_18_box[4].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
        north_18_box[5].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
    }

    halfwayline[0] = {{bounds[0].position.x, bounds[3].position.y / 2}};
    halfwayline[1] = {{bounds[1].position.x, bounds[3].position.y / 2}};

    // center circle
    center_circle = in_dimensions.center_circle;
    center_circle.setRadius(in_dimensions.center_circle.getRadius());
    center_circle.setCenter((in_dimensions.bounds.getSize().x) / 2, (in_dimensions.bounds.getSize().y) / 2);
    center_circle.setOutlineThickness(3);
    center_circle.setOutlineColor({255, 255, 255, 100});

    ////////////////////////////////////////////
    vlines = {// bounds
              bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5], bounds[6], bounds[7],

              // south 6 yard box
              south_6_box[0], south_6_box[1], south_6_box[2], south_6_box[3], south_6_box[4], south_6_box[5],

              // north 6 yard box
              north_6_box[0], north_6_box[1], north_6_box[2], north_6_box[3], north_6_box[4], north_6_box[5],

              // south 18 yard box
              south_18_box[0], south_18_box[1], south_18_box[2], south_18_box[3], south_18_box[4], south_18_box[5],

              // north 18 yard box
              north_18_box[0], north_18_box[1], north_18_box[2], north_18_box[3], north_18_box[4], north_18_box[5],

              // halfway line
              halfwayline[0], halfwayline[1]

    };
    for (auto& it : vlines) {
        it.color = {255, 255, 255, 100};
    }
}
//
//
//
void MiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    {  // background
        sf::RectangleShape bg;
        bg.setPosition(getGlobalBounds().left, getGlobalBounds().top);
        bg.setSize({getGlobalBounds().width, getGlobalBounds().height});
        bg.setFillColor({0, 0, 0, 100});
        bg.setOutlineThickness(0);
        target.draw(bg);
    }

    {  // lines
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        states.transform = transform;
        target.draw(vlines.data(), vlines.size(), sf::Lines, states);
    }

    {  // center circle
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        target.draw(center_circle, transform);
    }

    {  // ball
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        target.draw(ball, transform);
    }

    {  // players
        sf::Transform transform;
        transform.translate(getPosition());
        transform.scale(getScale().x, getScale().x);
        for (size_t i = 0; i < circles.size(); ++i) {
            target.draw(circles.at(i), transform);
        }
    }
}
//
//
//
sf::FloatRect MiniMap::getGlobalBounds() const {
    sf::FloatRect rect;
    rect.left = getPosition().x;
    rect.top = getPosition().y;
    rect.width = bounds[1].position.x * getScale().x;
    rect.height = bounds[3].position.y * getScale().x;
    return rect;
}
