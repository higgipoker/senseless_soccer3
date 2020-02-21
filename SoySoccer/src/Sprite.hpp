#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Renderable.hpp"

namespace SoySoccer {
class Sprite : public Renderable, public sf::Sprite {
   public:
    virtual void Render() override;
   protected:
};
}  // namespace SoySoccer
