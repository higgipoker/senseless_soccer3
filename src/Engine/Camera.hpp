#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>

#include "Engine/Controllable.hpp"
#include "Entity.hpp"

namespace Senseless {
// ***************************************************************************
// *                                                                         *
// * Camera                                                                  *
// *                                                                         *
// ***************************************************************************
class Camera : public Entity, public Controllable {
 public:
  Camera(float in_viewport_width, float in_viewport_height);
  void handleInput() override;
  void update(const float in_dt) override;
  void follow(Entity& in_entity);
  float getHeight();
  void setHeight(const float in_height);
  void setWorldRect(sf::FloatRect in_rect);
  sf::View& getView();
  sf::View& getHudView();
  void setHudView(sf::View in_view){hud_view = in_view;}
  sf::RectangleShape getRect();

 private:
  sf::View view;
  sf::View hud_view;
  sf::FloatRect world;
  Entity* following = nullptr;
  sf::CircleShape collider;
};

}  // namespace Senseless
