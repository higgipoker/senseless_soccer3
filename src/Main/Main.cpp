#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <sstream>

#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Controls/Joysticker.hpp"
#include "Engine/Folder.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerSprite.hpp"
#include "Team/Team.hpp"
#include "Team/TeamFactory.hpp"

using namespace Engine;
//
//
//
int main(int argc, char** args) {
    //
    // args
    //
    if (argc > 1) {
        std::cout << argc - 1 << " args: ";
        for (int i = 1; i < argc; ++i) {
            std::cout << args[i];
            if (i != argc - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    //
    // game resources
    //
    WorkingFolder working_folder;
    Folder graphics_folder(working_folder.getPath() + "/gfx");
    Folder data_folder(working_folder.getPath() + "/data");
    //
    // engine
    //
    sf::IntRect wnd_size{0, 0, 1280, 730};
    GameEngine engine("senseless soccer", wnd_size.width, wnd_size.height);
    //
    // pitch
    //
    UniquePtr<Pitch> pitch = std::make_unique<Pitch>(graphics_folder.getPath(true) + "grass_checked.png", world);
    engine.addSprite(pitch->getSprite(), engine.getBackgroundLayer());
    engine.addSprite(pitch->getMiniMap(), engine.getHudLayer());
    engine.getDebugUI().providePitch(pitch.get());

    //
    // teams
    //
    TeamFactory team_factory;
    Team team1 = team_factory.makeDefaultHomeTeam();
    Team team2 = team_factory.makeDefaultAwayTeam();

    //
    // match
    //
    Match match(std::move(pitch), team1, team2);

    match.getHomeTeam().addDefaultPlayers(match.getAwayTeam());
    //    match.getAwayTeam().addDefaultPlayers(match.getHomeTeam());

    for (size_t i = 0; i < match.getHomeTeam().numberPlayers(); ++i) {
        engine.addEntity(match.getHomeTeam().getPlayer(i));
        engine.addControllable(match.getHomeTeam().getPlayer(i));
    }
    for (size_t i = 0; i < match.getAwayTeam().numberPlayers(); ++i) {
        engine.addEntity(match.getAwayTeam().getPlayer(i));
        engine.addControllable(match.getAwayTeam().getPlayer(i));
    }
    //  if (match.getHomeTeam().hasPlayers()) {
    //    match.getHomeTeam().getPlayer().attachInput(engine.getDefaultGamepad());
    //  }

    match.getBall().movable.setPosition(match.getPitch().getDimensions().center_spot.getCenter().x,
                                        match.getPitch().getDimensions().center_spot.getCenter().y);

    engine.addEntity(match.getBall(), engine.getDefaultLayer());
    engine.getMainCamera().follow(match.getBall());

    // match.getHomeTeam().getPlayer().getBrain().changeState(brain_state::Retrieve);
    engine.addSprite(match.getHomeTeam().sprite);
    engine.addSprite(match.getAwayTeam().sprite);

    // test
    ProgressBar bar(40, 3, 50);
    match.getHomeTeam().getPlayer(0).power_bar = &bar;
    engine.addSprite(bar, engine.getDefaultLayer());

    srand(time(nullptr));

    Joysticker joysticker;
    joysticker.input = &engine.getDefaultGamepad();
    joysticker.team = &match.getHomeTeam();
    joysticker.power_bar = &bar;
    engine.getDefaultGamepad().attachListener(joysticker);

    engine.getMainCamera().setWorldRect(world);
    while (engine.isRunning()) {
        engine.step();
        match.update();
        // joysticker.update();
    }

    std::cout << args[0] << " exited normally" << std::endl;
    return 0;
}
