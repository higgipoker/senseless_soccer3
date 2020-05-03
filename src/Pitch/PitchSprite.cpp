#include "PitchSprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transform.hpp>

#include "Engine/Metrics.hpp"
#include "Engine/Texture.hpp"

using namespace Senseless;
//
//
//
void PitchSprite::init(const PitchDrawDimensions& in_dimensions,
                       const std::string& in_grass_texture) {
  setPosition(in_dimensions.origin.x, in_dimensions.origin.y);
  pitch_texture.create(static_cast<int>(in_dimensions.bounds.getSize().x + 4),
                       static_cast<int>(in_dimensions.bounds.getSize().y + 4));
  setTexture(pitch_texture.getTexture());

  // set up the repeating grass texture
  Texture tex_grass;
  sf::Sprite grass;
  if (!in_grass_texture.empty()) {
    tex_grass.loadFromFile(in_grass_texture);
    tex_grass.setRepeated(true);
    grass.setTexture(tex_grass);
    // size of the target rect for grass tile
    grass.setTextureRect(sf::IntRect{0, 0, static_cast<int>(pitch_texture.getSize().x),
                                     static_cast<int>(pitch_texture.getSize().y)});
  }

  // flip
  flip.rotate(180, {in_dimensions.bounds.getSize().x / 2, in_dimensions.bounds.getSize().y / 2});

  // draw grass and lines to the texture
  pitch_texture.clear(sf::Color(0, 0, 0, 0));
  pitch_texture.draw(grass);
  pitch_texture.draw(in_dimensions.draw_bounds_north);
  pitch_texture.draw(in_dimensions.draw_bounds_south, flip);
  pitch_texture.draw(in_dimensions.box_6);
  pitch_texture.draw(in_dimensions.box_6, flip);
  pitch_texture.draw(in_dimensions.box_18);
  pitch_texture.draw(in_dimensions.box_18, flip);
  pitch_texture.draw(in_dimensions.center_circle);
  pitch_texture.draw(in_dimensions.center_spot);
  pitch_texture.draw(in_dimensions.penalty_spot);
  pitch_texture.draw(in_dimensions.penalty_spot, flip);
  pitch_texture.draw(in_dimensions.arc_18);
  pitch_texture.draw(in_dimensions.arc_18, flip);
  pitch_texture.display();
}
//
//
//
void PitchSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite::draw(target, states);
}
