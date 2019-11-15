#include "MiniMap.hpp"
//
//
//
MiniMap::MiniMap() {
    scale_factor = 0.1F;
    scale.scale(scale_factor, scale_factor);
}
//
//
//
void MiniMap::init(const sf::FloatRect in_bounds, const PitchDimensions& in_dimensions,
                   const std::string& in_grass_texture) {
    // make a texture for drawing the lines on
    pitch_texture.create(in_dimensions.bounds.getSize().x * scale_factor + 4,
                         in_dimensions.bounds.getSize().y * scale_factor + 4);

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

    const int dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.south_6.getSize().y * 2);

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
    south_18_box[3] = {{south_18_box[1].position.x + in_dimensions.south_18.getSize().x, south_18_box[1].position.y}};

//    // |
    south_18_box[4] = south_18_box[3];
    south_18_box[5] = {{south_18_box[3].position.x, south_18_box[0].position.y}};

    north_18_box[0] = south_18_box[0];
    north_18_box[1] = south_18_box[1];
    north_18_box[2] = south_18_box[2];
    north_18_box[3] = south_18_box[3];
    north_18_box[4] = south_18_box[4];
    north_18_box[5] = south_18_box[5];

    const int dis_from_box_to_box = in_dimensions.bounds.getSize().y - (in_dimensions.south_18.getSize().y * 2);

    north_18_box[0].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
    north_18_box[1].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
    north_18_box[2].position.y -= dis_from_box_to_box;
    north_18_box[3].position.y -= dis_from_box_to_box;
    north_18_box[4].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
    north_18_box[5].position.y -= (dis_from_box_to_box + in_dimensions.south_18.getSize().y);
    }

    halfwayline[0] = {{bounds[0].position.x, bounds[3].position.y/2}};
    halfwayline[1] = {{bounds[1].position.x, bounds[3].position.y/2}};
}
//
//
//
void MiniMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vertex lines[] = {
        // bounds
        bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5], bounds[6], bounds[7],

        // south 6 yard box
        south_6_box[0], south_6_box[1], south_6_box[2], south_6_box[3], south_6_box[4], south_6_box[5],

        // north 6 yard box
        north_6_box[0], north_6_box[1], north_6_box[2], north_6_box[3], north_6_box[4], north_6_box[5],

        // south 18 yard box
        south_18_box[0], south_18_box[1], south_18_box[2], south_18_box[3], south_18_box[4], south_18_box[5],

        // north 18 yard box
        north_18_box[0], north_18_box[1], north_18_box[2], north_18_box[3], north_18_box[4], north_18_box[5],

        //halfway line
        halfwayline[0], halfwayline[1]

    };
    states.transform = scale;
    target.draw(lines, 34, sf::Lines, states);
    // target.draw(sprite);
}
