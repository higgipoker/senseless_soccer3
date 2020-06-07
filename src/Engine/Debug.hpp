#pragma once
#ifndef NDEBUG

#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"

#include "Match/Match.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace Senseless {
/**
 * @brief The Debug class
 */
class Debug {
   public:
    Debug   (sf::RenderWindow &in_window);
    ~Debug  ();

    void prep               (const int in_frames, const int in_frametime);
    void draw               ();
    void handleInput        (sf::Event &in_event);

    static void show            ();
    static void hide            ();
    static void toggle          ();
    static bool showHud         ();
    static bool drawBounds      ();
    static bool drawDiagnostics ();

    static sf::Color defaultBoundsColor         ();
    static sf::Color defaultDiagnosticsColor    ();

    static Entity*      picked;
    static Vector3      picked_position_screen;
    static Match*   match;

   private:
    sf::RenderWindow&   window;
    sf::Clock           ui_clock;
    Vector3             mouse_position;
    int                 framecount = 0;
    int                 frametime = 0;

    static sf::Color    bounds_color;
    static sf::Color    disgnostics_color;


    static void draw_team_menu(int which_team=0);

    //
    // main window stuff
    //
    void draw_main_window   ();
    static bool         flag_draw_bounds;
    static bool         flag_draw_diagnostics;
    static bool         show_debug_hud;
    static float        mini_map_scale_factor;
    static int          home_team_positioning;
    static int          away_team_positioning;
    static int          home_pitch_side;
    static int          away_pitch_side;
    static int          attacking_team;
    static int          active_team;

    //
    // player window stuff
    //
    void draw_player_window ();
    static int brainstate;
};

}  // namespace Senseless
#endif
