#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/System.hpp>
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

#include <SFML/System.hpp>
#include <mutex>
#include <thread>

void threadCallback(int id, bool *in) {
    static std::mutex mutex;
    while (*in) {
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Hello, World " << id << std::endl;
    }
}

using namespace Engine;
//
//
//
int main(int argc, char **args) {
    bool running = true;
    const int num_threads = 10000;

    std::thread t[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(threadCallback, i + 1, &running);
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
    sf::IntRect wnd_size{0, 0, 1280, 720};
    GameEngine engine("senseless soccer", wnd_size.width, wnd_size.height);
    //
    // pitch
    //
    auto pitch = std::make_unique<Pitch>(graphics_folder.getPath(true) + "grass_checked.png", world);
    engine.addSprite(pitch->getSprite(), engine.getBackgroundLayer());
    engine.addEntity(pitch->getMiniMapEntity(), engine.getHudLayer());
    pitch->getMiniMapEntity().movable.position = {20, 20};

    //
    // teams
    //
    TeamFactory team_factory;
    Team team1 = team_factory.makeDefaultHomeTeam("Team1");
    Team team2 = team_factory.makeDefaultAwayTeam("Team2");
    //
    // match
    //
    Match match(std::move(pitch), team1, team2);
    engine.getDebugUI().match = &match;
    match.getHomeTeam().addDefaultPlayers(match.getAwayTeam());
    match.getAwayTeam().addDefaultPlayers(match.getHomeTeam());

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

    // puts the ball on the center spot
    match.getBall().movable.position =
        (match.getPitch().toScreenSpace({match.getPitch().getDimensions().center_spot.getCenter().x,
                                         match.getPitch().getDimensions().center_spot.getCenter().y}));

    engine.addEntity(match.getBall(), engine.getDefaultLayer());
    engine.getMainCamera().follow(match.getBall());

    // match.getHomeTeam().getPlayer().getBrain().changeState(brain_state::Retrieve);
    engine.addSprite(match.getHomeTeam().sprite);
    engine.addSprite(match.getAwayTeam().sprite);

    // test
    ProgressBar bar(40, 3, 50);
    match.getHomeTeam().getPlayer(0).power_bar = &bar;
    engine.addSprite(bar, engine.getDefaultLayer());

    srand(static_cast<unsigned int>(time(nullptr)));

    Joysticker joysticker;
    joysticker.input = &engine.getDefaultGamepad();
    joysticker.team = &match.getHomeTeam();
    joysticker.power_bar = &bar;
    engine.getDefaultGamepad().attachListener(joysticker);

    engine.getMainCamera().setWorldRect(world);
    while (engine.isRunning()) {
        engine.step();
        auto v1 = match.getHomeTeam().getPlayerPositions();
        auto v2 = match.getAwayTeam().getPlayerPositions();
        std::vector<Engine::Vector3> v3;
        for (auto &i : v1) {
            v3.push_back(i);
        }
        for (auto &i : v2) {
            v3.push_back(i);
        }
    }
    running = false;
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }
    std::cout << args[0] << " exited normally" << std::endl;
    return 0;
}
