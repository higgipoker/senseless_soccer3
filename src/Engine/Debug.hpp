#pragma once
#ifndef NDEBUG

#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"

#include "Game/Game.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace Senseless {
/**
 * @brief The Debug class
 */
class Debug {
   public:
    Debug(sf::RenderWindow &in_window);
    ~Debug();
    void prep(const int in_frames, const int in_frametime)  ;
    void draw();
    void draw_main_window();
    void draw_player_window();
    void handleInput(sf::Event &in_event);
    static void show();
    static void toggle();
    static bool showHud();
    static bool drawBounds();
    static bool drawDiagnostics();
    static sf::Color defaultBoundsColor();
    static sf::Color defaultDiagnosticsColor();

    static Entity *picked;
    static Vector3 picked_position_screen;
    static GameState *gamestate;

   private:
    /// target window
    sf::RenderWindow &window;
    /// a clock for ui tick
    sf::Clock ui_clock;
    /// track mouse
    Vector3 mouse_position;
    /// data
    int framecount = 0;
    int frametime = 0;
    /// debug flags
    static bool flag_draw_bounds;
    static sf::Color bounds_color;
    static bool flag_draw_diagnostics;
    static sf::Color disgnostics_color;  

    /// display debug gui?
    static bool show_debug_hud;
    static float mini_map_scale_factor;

    static int home_team_positioning;
    static int away_team_positioning;
    static int home_pitch_side;
    static int away_pitch_side;
    static int attacking_team;
    static int active_team;

    static void draw_team_menu(int which_team=0);
};

}  // namespace Senseless
#endif
