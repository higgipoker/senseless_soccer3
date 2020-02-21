#include "Texture.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
//
// gets the texture displayable by a sfml window or sprite
//
const sf::Texture &Texture::get() {
    return merged_texture.getTexture();
}
//
// merges multiple spritesheets into one single texture (vertically)
//
bool Texture::merge(std::initializer_list<sf::Texture *> textures) {
    // find width of eventual texture
    int width = 0;
    for (auto &tex : textures) {
        if (tex->getSize().x > width) {
            width = tex->getSize().x;
        }
    }

    // find height of eventual texture
    int height = 0;
    for (auto &tex : textures) {
        height += tex->getSize().y;
    }

    if (merged_texture.create(width, height) != true) {
        std::cout << "Could not create texture with dimensions " << width << ", " << height << std::endl;
        return false;
    }

    merged_texture.clear({0, 0, 0, 0});
    int y = 0;
    for (auto &tex : textures) {
        sf::Sprite sprite(*tex);
        sprite.move(0, y);
        merged_texture.draw(sprite);
        y += sprite.getLocalBounds().height;
    }
    merged_texture.display();

    return true;
}
//
// changes all pixels of one color to another color for a list of pairs of colors (palette)
//
void Texture::changeColors(sf::Texture &in_texture, const std::vector<std::pair<sf::Color, sf::Color> > &in_palette) {
    sf::Image img = in_texture.copyToImage();

    for (auto &colours : in_palette) {
        for (unsigned int x = 0; x < img.getSize().x; ++x) {
            for (unsigned int y = 0; y < img.getSize().y; ++y) {
                if (img.getPixel(x, y) == colours.first) {
                    img.setPixel(x, y, colours.second);
                }
            }
        }
    }
    in_texture.loadFromImage(img);
}
