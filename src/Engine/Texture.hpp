#pragma once
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <map>
namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * Texture                                                                 *
// *                                                                         *
// ***************************************************************************
class Texture : public sf::Texture {
    public:
        void swapColors     (const std::vector<std::pair<sf::Color, sf::Color>>& in_palette);

    private:
        std::string loaded_file;
        static int  ref;
};
// ***************************************************************************
}  // namespace Senseless
