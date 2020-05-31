#pragma once

#include "Entity.hpp"

#include "Engine/Controllable.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>

namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * Camera                                                                  *
// *                                                                         *
// ***************************************************************************
class Camera : public Entity, public Controllable {
    public:                        
    void                handleInput     () override;
    void                update          (const float in_dt) override;
    void                follow          (Entity &in_entity);
    float               getHeight       ();
    void                setHeight       (const float in_height);
    void                setWorldRect    (sf::FloatRect in_rect);
    sf::View&           getview         ();
    sf::RectangleShape  getRect         ();

    private:
    sf::View            view;
    sf::FloatRect       world;
    Entity*             following = nullptr;
    sf::CircleShape     collider;

   private:
   Camera          (float in_viewport_width, float in_viewport_height);
   public:
    friend class EntityFactory;
};

}  // namespace Senseless
