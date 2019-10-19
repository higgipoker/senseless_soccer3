#pragma once
#include "Player.hpp"

#include <SFML/Graphics/Texture.hpp>
//
//
//
class PlayerFactory {
 public:
  static std::unique_ptr<Player> makePlayer(std::shared_ptr<sf::Texture> in_spritesheet);
};
