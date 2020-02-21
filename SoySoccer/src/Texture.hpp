#pragma once
#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/RenderTexture.hpp>

#include <initializer_list>
#include <iostream>

#include <map>
//
//
//
class Texture {
   public:
    //
    //
    //
    bool merge(std::initializer_list<sf::Texture *> textures);
    //
    //
    //
    static void changeColors(sf::Texture & in_texture, const std::vector<std::pair<sf::Color, sf::Color>>& in_palette);
    //
    //
    //
    const sf::Texture& get(void);

   private:
    sf::RenderTexture merged_texture;
};
