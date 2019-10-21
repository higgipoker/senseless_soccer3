#pragma once
#include "Player.hpp"

#include "Engine/Types.hpp"

#include <SFML/Graphics/Texture.hpp>
//
//
//
class PlayerFactory {
 public:
  static UnqPtr<Player> makePlayer(SharedPtr<sf::Texture> in_spritesheet);
};
