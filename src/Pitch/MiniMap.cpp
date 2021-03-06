#include "MiniMap.hpp"

#include "Utils.hpp"
namespace Senseless {
//
//
//
MiniMap::MiniMap(Team &in_home_team, Team &in_away_team, Ball &in_ball, Pitch &in_pitch, Camera &in_camera)
    : Entity(std::make_unique<MiniMapSprite>(), std::make_unique<Sprite>()),
      home_team(in_home_team),
      away_team(in_away_team),
      ball(in_ball),
      pitch(in_pitch),
      camera(in_camera) {
    getSprite().init(pitch.getDimensions());
    name = "mini map";
}
//
//
//
void MiniMap::update(const float in_dt) {
    renderable.sprite->setPosition(movable.position.x, movable.position.y);
    movable.setBounds(renderable.sprite->getGlobalBounds());
    auto positions = join_vectors(home_team.getPlayerPositions(), away_team.getPlayerPositions());
//     auto cam = camera.getRect();
//     auto pitchpos = Vector3{cam.getPosition().x, cam.getPosition().y};
//     cam.setPosition(pitchpos.x, pitchpos.y);
    getSprite().update(pitch.movable.position, positions, ball.movable.position, camera.getRect());
}
//
//
//
MiniMapSprite &MiniMap::getSprite() {
    return static_cast<MiniMapSprite &>(*renderable.sprite);
}
}  // namespace Senseless
