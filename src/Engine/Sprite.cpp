#include "Sprite.hpp"

#include <math.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

#include "Debug.hpp"
#include "Metrics.hpp"
#include "Vector.hpp"
//
//
//
namespace Senseless {
//
//
//
Sprite::Sprite() {
}
//
//
//
Sprite::Sprite(const sf::Texture &texture) : sf::Sprite(texture) {
}
//
//
//
void Sprite::init(const SpriteSetDefinition &in_def) {
    int x           = in_def.frame_width * in_def.start_col;
    int y           = in_def.vertical_offset + in_def.frame_height * in_def.start_row;
    int col         = in_def.start_col;
    int frame_count = in_def.spriteset_frames;
    while (--frame_count >= 0) {
        sf::IntRect rect;
        rect.left   = x;
        rect.top    = y;
        rect.width  = in_def.frame_width;
        rect.height = in_def.frame_height;
        frames.push_back(rect);

        // next col
        x += in_def.frame_width;

        // next row
        if (++col == in_def.sheet_cols) {
            x = 0;
            y += in_def.frame_height;
            col = 0;
        }
    }
    setFrame(current_frame);

    // default set origin to center
    setOrigin(static_cast<float>(in_def.frame_width / 2),
              static_cast<float>(in_def.frame_height / 2));

    // for perspective scaling
    perspective_width = getLocalBounds().width;
}
//
//
//
void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite::draw(target, states);
#ifndef NDEBUG
    if (Debug::showHud() && Debug::drawBounds()) {
        sf::RectangleShape bounds{sf::Vector2f{getGlobalBounds().width, getGlobalBounds().height}};
        bounds.setPosition({getGlobalBounds().left, getGlobalBounds().top});
        bounds.setFillColor(sf::Color::Transparent);
        bounds.setOutlineColor(Debug::defaultBoundsColor());
        bounds.setOutlineThickness(1);

        target.draw(bounds);
    }
    if (Debug::showHud() && Debug::drawDiagnostics()) {
        for (auto &shape : debug_shapes) {
            target.draw(*shape);
        }
    }
#endif
}
//
//
//
void Sprite::setFrame(const int in_frame) {
    current_frame = in_frame;
    setTextureRect(frames.at(current_frame));
}
//
//
//
int Sprite::getFrame() {
    return current_frame;
}
//
//
//
void Sprite::setAnimation(SpriteAnimation *in_animation, bool in_autostart) {
    if (in_animation == animation)
        return;
    animating = in_autostart;
    animation = in_animation;
    setTextureRect(frames.at(animation->currentFrame()));
}
//
//
//
void Sprite::animate() {
    if (animation && animating) {
        animation->step();
        current_frame = animation->currentFrame();
        setTextureRect(frames.at(current_frame));
    }
}
//
//
//
void Sprite::startAnimating() {
    animating = true;
}
//
//
//
void Sprite::stopAnimating() {
    animating = false;
}
//
//
//
void Sprite::perspectivize(const float in_camera_height) {
    if (perspectivizable) {
        // size depending on distance from camera
        float dimensions       = perspective_width;
        float dist_from_camera = in_camera_height - *entity_z;

        // other side of camera, don't perspectivize!
        if (dist_from_camera <= 0) {
            setScale({0.f, 0.f});
            shadow->setScale(100, 100);
            return;
        }

        float angular_diameter    = 2 * (atanf(dimensions / (2 * dist_from_camera)));
        float degs                = Degrees(angular_diameter);
        float sprite_scale_factor = degs / dimensions;
        float sprite_ratio        = dimensions / getLocalBounds().width;
        sprite_scale_factor *= sprite_ratio;
        setScale(sprite_scale_factor, sprite_scale_factor);
        shadow->setScale(sprite_scale_factor, sprite_scale_factor);

        // y offset due to height
        float z_cm = *entity_z * Z_PERSP_OFFSET;
        if (Math::greater_than(z_cm, 0)) {
            float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
            move(0, -y_offset);
        }
    }
}
//
//
//
void Sprite::setBasePerspectiveWidth(const float in_width) {
    perspective_width = in_width;
}
//
//
//
void Sprite::setPerspectivizable(bool in_status) {
    perspectivizable = in_status;
}
}  // namespace Senseless
