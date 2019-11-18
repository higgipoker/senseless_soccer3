#include "Texture.hpp"
namespace Engine {
int Texture::ref = 0;
//
//
//
bool Texture::loadFromFile(const std::string& filename, const sf::IntRect& area) {
    loaded_file = filename;
    //std::cout << ++ref << " textures loaded ( " << filename << ")" << std::endl;
    return sf::Texture::loadFromFile(filename, area);
}
//
//
//
void Texture::swapColors(const std::vector<std::pair<sf::Color, sf::Color> >& in_palette) {
    sf::Image img = copyToImage();

    for (auto& colours : in_palette) {
        for (unsigned int x = 0; x < img.getSize().x; ++x) {
            for (unsigned int y = 0; y < img.getSize().y; ++y) {
                if (img.getPixel(x, y) == colours.first) {
                    img.setPixel(x, y, colours.second);
                }
            }
        }
    }
    loadFromImage(img);
}
}  // namespace Engine
