#pragma once
#ifndef NDEBUG

#include "Pitch/Pitch.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace Engine {
/**
 * @brief The Debug class
 */
class Debug {
   public:
    //
    //
    //
    Debug(sf::RenderWindow &in_window);
    //
    //
    //
    ~Debug();
    //
    //
    //
    void update(const int in_frames, const int in_frametime);
    //
    //
    //
    void handleInput(sf::Event &in_event);
    //
    //
    //
    static void show();
    //
    //
    //
    static void toggle();
    //
    //
    //
    static bool showHud();
    //
    //
    //
    static bool drawBounds();
    //
    //
    //
    static bool drawDiagnostics();
    //
    //
    //
    static sf::Color defaultBoundsColor();
    //
    //
    //
    static sf::Color defaultDiagnosticsColor();
    //
    //
    //
    static void providePitch(Pitch *in_pitch) {
        pitch = in_pitch;
    };

   private:
    /// target window
    sf::RenderWindow &window;
    /// a clock for ui tick
    sf::Clock ui_clock;
    /// track mouse
    float mouse_x = 0;
    float mouse_y = 0;

    /// debug flags
    static bool flag_draw_bounds;
    static sf::Color bounds_color;
    static bool flag_draw_diagnostics;
    static sf::Color disgnostics_color;

    /// display debug gui?
    static bool show_debug_hud;

    /// tmp
    static Pitch *pitch;
    static float mini_map_scale_factor;
};

}  // namespace Engine
#endif
