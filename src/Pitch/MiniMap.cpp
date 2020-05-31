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
    getSprite().init(pitch.getDrawDimensions());
}
//
//
//
void MiniMap::update(const float in_dt) {
    renderable.sprite->setPosition(movable.position.toSfVector());
    movable.setBounds(renderable.sprite->getGlobalBounds());
    auto positions = join_vectors(home_team.getPlayerPositions(), away_team.getPlayerPositions());
    auto cam = camera.getRect();
    auto pitchpos = pitch.toPitchSpace(Vector3{cam.getPosition().x, cam.getPosition().y});
    cam.setPosition(pitchpos.x, pitchpos.y);
    getSprite().update(positions, pitch.toPitchSpace(ball.movable.position), cam);
}
}  // namespace Senseless
