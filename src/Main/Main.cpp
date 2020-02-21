
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

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
#include <sstream>
#include <thread>
//
//
//
void threadCallback(int id, bool *in) {
    static std::mutex mutex;
    int i = 0;
    int cnt = 0;
    while (i < 1000000) {
        // while (*in) {
        const std::lock_guard<std::mutex> lock(mutex);
        cnt = i / 0.3F;
        ++cnt;
        ++i;
        //    std::cout << "thread " << id << " is doing work..." << std::endl;
    }

    std::cout << "thread " << id << " done" << std::endl;
}

using namespace Engine;
//
//
//
template <class T>
std::vector<T> join_vectors(const std::vector<T> &_v1, const std::vector<T> &_v2) {
    std::vector<T> v3;
    v3.reserve(_v1.size() + _v2.size());
    v3.insert(v3.end(), _v1.begin(), _v1.end());
    v3.insert(v3.end(), _v2.begin(), _v2.end());
    return v3;
}
//
//
//
int main(int argc, char **args) {
    //
    // thread test
    //
    bool running = true;
    const int num_threads = 10;
    std::array<std::thread,num_threads> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.at(i) = std::thread(threadCallback, i + 1, &running);
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
    Team team1 = TeamFactory::makeDefaultHomeTeam("Team1");
    Team team2 = TeamFactory::makeDefaultAwayTeam("Team2");
    //
    // match
    //
    Match match(std::move(pitch), team1, team2);
    engine.getDebugUI().match = &match;
    match.getAwayTeam().addDefaultPlayers(match.getHomeTeam());
    match.getHomeTeam().addDefaultPlayers(match.getAwayTeam());
    //
    // gamestate
    //
    gamestate.match = &match;
    gamestate.home_team = &match.getHomeTeam();
    gamestate.away_team = &match.getAwayTeam();
    gamestate.ball = &match.getBall();
    gamestate.pitch = &match.getPitch();
    gamestate.minimap = static_cast<MiniMap *>(&match.getPitch().getMiniMapSprite());
    //
    // set up engine with entities
    //
    for (size_t i = 0; i < gamestate.home_team->numberPlayers(); ++i) {
        engine.addEntity(gamestate.home_team->getPlayer(i));
        engine.addControllable(gamestate.home_team->getPlayer(i));
    }
    for (size_t i = 0; i < gamestate.away_team->numberPlayers(); ++i) {
        engine.addEntity(gamestate.away_team->getPlayer(i));
        engine.addControllable(gamestate.away_team->getPlayer(i));
    }
    //  if (match.getHomeTeam().hasPlayers()) {
    //    match.getHomeTeam().getPlayer().attachInput(engine.getDefaultGamepad());
    //  }

    // puts the ball on the center spot
    gamestate.ball->movable.position =
        gamestate.pitch->toScreenSpace({gamestate.pitch->getDimensions().center_spot.getCenter().x,
                                        gamestate.pitch->getDimensions().center_spot.getCenter().y});

    engine.addEntity(*gamestate.ball, engine.getDefaultLayer());
    engine.getMainCamera().follow(*gamestate.ball);

    // match.getHomeTeam().getPlayer().getBrain().changeState(brain_state::Retrieve);
    engine.addSprite(gamestate.home_team->sprite);
    engine.addSprite(gamestate.away_team->sprite);

    // test
//    ProgressBar bar(40, 3, 50);
//    gamestate.home_team->getPlayer(0).power_bar = &bar;
//    engine.addSprite(bar, engine.getDefaultLayer());

    srand(static_cast<unsigned int>(time(nullptr)));

    Joysticker joysticker;
    joysticker.input = &engine.getDefaultGamepad();
    joysticker.team = gamestate.home_team;
    //joysticker.power_bar = &bar;
    engine.getDefaultGamepad().attachListener(joysticker);

    engine.getMainCamera().setWorldRect(world);

    while (engine.isRunning()) {
        engine.step();
        auto positions =
            join_vectors(gamestate.home_team->getPlayerPositions(), gamestate.away_team->getPlayerPositions());

        gamestate.minimap->updatePlayerPositions(positions,
                                                 gamestate.pitch->toPitchSpace(match.getBall().movable.position));
        match.update();
        // joysticker.update();
    }
    running = false;
    for (int i = 0; i < num_threads; ++i) {
        threads.at(i).join();
    }

    std::cout << args[0] << " exited normally" << std::endl;
    return 0;
}
