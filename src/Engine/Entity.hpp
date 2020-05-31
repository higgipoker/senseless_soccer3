#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Renderable.hpp"
#include "Compass.hpp"
#include "Movable.hpp"
#include "Sprite.hpp"
#include "Types.hpp"
namespace Senseless {
struct GameState;
static const float SHADOW_OFFSET  = 2;
static const bool  DRAW_RAYS = false;

// ------------------------
// possible types of entity
// ------------------------
enum class EntityType { Unknown, Player, Ball, Camera, Pitch };
class Entity {
   public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
    virtual        ~Entity      (){};
    virtual void    update      (const float in_dt);

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

    static GameState *gamestate;

   protected:
    // -----------------------------------------------------------------------
    // force all entities to be acquired through the factory
    // -----------------------------------------------------------------------
    Entity      (std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow);
};

}  // namespace Senseless
