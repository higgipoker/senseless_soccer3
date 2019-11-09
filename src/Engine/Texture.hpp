#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include <map>
namespace Engine {
//
//
//
class Texture : public sf::Texture {
   public:
    //
    //
    //
    virtual ~Texture() {
        std::cout << "Destruct Texture (" << loaded_file << "), " << --ref << " textures remaining"
                  << std::endl;
    }
    //
    //
    //
    bool loadFromFile(const std::string& filename, const sf::IntRect& area = sf::IntRect()) override;
    //
    //
    //
    void swapColors(const std::vector<std::pair<sf::Color, sf::Color>>& in_palette);

   private:
    std::string loaded_file;
    static int ref;
};
}  // namespace Engine
