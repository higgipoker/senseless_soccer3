#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Renderable.hpp"
#include "Compass.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Types.hpp"
namespace Senseless {
static const float SHADOW_OFFSET  = 2;
static const bool  DRAW_RAYS = false;

// ------------------------
// possible types of entity
// ------------------------
enum class EntityType { Unknown, Player, Ball };
class Entity {
   public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
                    Entity      (UniquePtr<Sprite> in_sprite, UniquePtr<Sprite> in_shadow);
    virtual void    update      ();

    // -----------------------------------------------------------------------
    // members
    // -----------------------------------------------------------------------
    Movable         movable;
    Renderable      renderable;
    std::string     name;
    EntityType      type        = EntityType::Unknown;

    // -----------------------------------------------------------------------
    // debug
    // -----------------------------------------------------------------------
    sf::RectangleShape xray;
    sf::RectangleShape yray;
};

}  // namespace Senseless
