#pragma once

#include "SpriteAnimation.hpp"

#include "Types.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Senseless {
//
//
//
struct SpriteSetDefinition {
    int vertical_offset = 0;
    int frame_width = 0;
    int frame_height = 0;
    int spriteset_frames = 0;
    int start_row = 0;
    int start_col = 0;
    int sheet_cols = 0;
};
//
//
//
class Sprite : public sf::Sprite {
   public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
                 Sprite                  ();
                 Sprite                  (const sf::Texture& texture);
                 Sprite                  (SharedPtr<sf::Texture> in_texture);
            void init                    (const SpriteSetDefinition& in_def);
            void setFrame                (const int in_frame);
            int  getFrame                ();
            void animate                 ();
            void startAnimating          ();
            void stopAnimating           ();
            void setBasePerspectiveWidth (const float in_width);
            void setPerspectivizable     (bool in_status);
            void draw                    (sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
    virtual void setAnimation            (SpriteAnimation* in_animation, bool in_autostart = true);
    virtual void perspectivize           (const float in_camera_height);

    // -----------------------------------------------------------------------
    // members
    // -----------------------------------------------------------------------
    float*                      entity_z = nullptr;
    Sprite*                     shadow = nullptr;
    std::vector<sf::Shape*>     debug_shapes;

   protected:
    std::vector<sf::IntRect>    frames;
    SpriteAnimation*            animation = nullptr;
    int                         current_frame = 0;
    bool                        animating = false;
    bool                        perspectivizable = false;
    float                       perspective_width = 0;

    void draw_debug(sf::RenderTarget& target) const;
};
}  // namespace Senseless
