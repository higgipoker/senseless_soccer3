#include "EntityFactory.h"

#include "../Ball/BallSprite.hpp"

namespace Senseless {
//
//
//
Player& EntityFactory::newPlayer(const sf::Texture& match_texture, const TeamStrip in_strip) {
    auto shadow = std::make_unique<PlayerShadowSprite>(match_texture);
    auto sprite = std::make_unique<PlayerSprite>(match_texture, in_strip);
    auto player = std::make_unique<Player>(std::move(sprite), std::move(shadow));
    entities.emplace_back(std::move(player));
    return dynamic_cast<Player&>(*entities.back().get());
}
//
//
//
Ball& EntityFactory::newBall(const sf::Texture& match_texture) {
    auto shadow = std::make_unique<BallSprite>(match_texture);
    auto sprite = std::make_unique<BallSprite>(match_texture);
    auto ball   = std::unique_ptr<Ball>(new Ball(std::move(sprite), std::move(shadow)));
    entities.emplace_back(std::move(ball));
    return dynamic_cast<Ball&>(*entities.back().get());
}
//
//
//
Camera& EntityFactory::newCamera(float in_width, float in_height) {
    auto camera = std::unique_ptr<Camera>(new Camera(in_width, in_height));
    entities.emplace_back(std::move(camera));
    return dynamic_cast<Camera&>(*entities.back().get());
}
//
//
//
Pitch& EntityFactory::newPitch(const std::string& in_grass_texture) {
    auto pitch = std::unique_ptr<Pitch>(new Pitch(in_grass_texture));
    entities.emplace_back(std::move(pitch));
    return dynamic_cast<Pitch&>(*entities.back().get());
}
//
//
//
MiniMap& EntityFactory::newMiniMap(Team& in_home_team, Team& in_away_team, Ball& in_ball, Pitch& in_pitch, Camera& in_camera) {
    auto minimap = std::unique_ptr<MiniMap>(new MiniMap(in_home_team, in_away_team, in_ball, in_pitch, in_camera));
    entities.emplace_back(std::move(minimap));
    return dynamic_cast<MiniMap&>(*entities.back().get());
}
//
//
//
void EntityFactory::release(Entity* in_entity) {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if ((*it).get() == in_entity) {
            entities.erase(it);
        }
    }
}
//
//
//
void EntityFactory::reset() {
    entities.clear();
}

}  // namespace Senseless
