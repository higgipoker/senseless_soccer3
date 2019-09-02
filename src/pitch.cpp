#include "pitch.hpp"
///
///
///
void init_pitch(Pitch &pitch, const std::string &grass_spritesheet,
                Camera &camera) {
  init_grass(pitch.grass, grass_spritesheet, camera);
}
//
//
//
void update_pitch(Pitch &pitch, Camera &camera) {
  update_grass(pitch.grass, camera);
}
