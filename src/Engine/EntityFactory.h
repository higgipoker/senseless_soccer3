#pragma once
#include "Entity.hpp"
#include "../Player/Player.hpp"
#include "../Player/PlayerSprite.hpp"
#include "../Team/Team.hpp"
#include "../Ball/Ball.hpp"
#include "../Engine/Camera.hpp"
#include "../Pitch/Pitch.hpp"
#include "../Pitch/MiniMap.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <vector>

namespace Senseless {
class EntityFactory {
   public:
    Player&  newPlayer   (const sf::Texture& match_texture, const TeamStrip in_strip);
    Ball&    newBall     (const sf::Texture &match_texture);
    Camera&  newCamera   (float in_width, float in_height);
    Pitch&   newPitch    (const std::string &in_grass_texture);
    MiniMap& newMiniMap  (Team& in_home_team, Team& in_away_team, Ball& in_ball, Pitch& in_pitch, Camera& in_camera);
    void     release     (Entity* in_entity);
    void     reset       ();
   private:
    std::vector<std::unique_ptr<Entity>> entities;
};
}  // namespace Senseless
