
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/System.hpp>
#include <mutex>
#include <sstream>
#include <thread>

#include "Engine/EntityFactory.h"
#include "Ball/Ball.hpp"
#include "Ball/BallSprite.hpp"
#include "Controls/Joysticker.hpp"
#include "Engine/Folder.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/ProgressBar.hpp"
#include "Engine/Texture.hpp"
#include <memory>
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include "Pitch/MiniMapSprite.h"
#include "Pitch/Pitch.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerSprite.hpp"
#include "Team/Team.hpp"
#include "Team/TeamFactory.hpp"
#include "Team/PositionFactory.h"
//
//
//
using namespace Senseless;
void threadCallback(int id, bool *in) {
    static std::mutex mutex;
    int               i   = 0;
    int               cnt = 0;
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

using namespace Senseless;
//
//
//
int main(int argc, char **args) {
    //
    // thread test
    //
    //    bool running     = true;
    //    const int num_threads = 10;
    //    std::array<std::thread, num_threads> threads;
    //    for (int i = 0; i < num_threads; ++i) {
    //        threads.at(i) = std::thread(threadCallback, i + 1, &running);
    //    }
    //
    // game resources
    //
    EntityFactory entity_factory;
    WorkingFolder working_folder;
    Folder        graphics_folder(working_folder.getPath() + "/gfx");
    Folder        data_folder(working_folder.getPath() + "/data");
    //
    // engine
    //
    sf::IntRect wnd_size{0, 0, 1280, 720};
    Camera &    camera = entity_factory.newCamera(wnd_size.width, wnd_size.height);
    GameEngine  engine(camera, "senseless soccer", wnd_size.width, wnd_size.height);
    //
    // pitch
    //
    Pitch &pitch = entity_factory.newPitch(graphics_folder.getPath(true) + "grass_checked.png");
    engine.addEntity(pitch, engine.getBackgroundLayer());
    //
    // teams
    //
    Team team1 = TeamFactory::makeDefaultHomeTeam("Team1");
    Team team2 = TeamFactory::makeDefaultAwayTeam("Team2");
    //
    // match and ball
    //
    Match match(pitch, team1, team2);
    Ball &ball = entity_factory.newBall(match.getMatchTexture());
    ball.renderable.sprite->setPerspectivizable(true);
    ball.name = "Ball";
    match.setBall(ball);
    engine.getDebugUI().gamestate = &gamestate;
    //
    // mini map
    //
    MiniMap &minimap         = entity_factory.newMiniMap(team1, team2, ball, pitch, engine.getMainCamera());
    minimap.name             = "mini map";
    minimap.movable.position = {10, 10};
    engine.addEntity(minimap, engine.getHudLayer());

    // add players to team 1
    PositionFactory positions;
    auto            right_center_forward = positions.newCenterForward(pitch, team1, team2);
    right_center_forward->applyModifier(PositionModifier::Right);
    right_center_forward->name = "Right Center Forward";
    Player &player             = entity_factory.newPlayer(match.getMatchTexture(), TeamStrip::Home);
    player.match               = &match;
    player.my_team             = &team1;
    player.other_team          = &team2;
    TeamData td;
    td.shirt_number = 10;
    player.name     = right_center_forward->name;
    player.setTeamData(td);
    player.setPlayingPosition(std::move(right_center_forward));
    player.movable.position = pitch.toScreenSpace({0, pitch.getDimensions().halfway_line.getPosition().y});
    team1.addPlayer(&player);
    team1.goToSetPiecePositions(Situation::KickOff);
    //
    // gamestate
    //
    gamestate.match     = &match;
    gamestate.home_team = &match.getHomeTeam();
    gamestate.away_team = &match.getAwayTeam();
    gamestate.ball      = &match.getBall();
    gamestate.pitch     = &match.getPitch();
    gamestate.minimap   = &minimap;
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
    gamestate.ball->movable.position = gamestate.pitch->toScreenSpace({gamestate.pitch->getDimensions().center_spot.getCenter().x, gamestate.pitch->getDimensions().center_spot.getCenter().y});

    engine.addEntity(*gamestate.ball, engine.getDefaultLayer());
    engine.getMainCamera().follow(*gamestate.ball);

    // match.getHomeTeam().getPlayer().getBrain().changeState(brain_state::Retrieve);
    //  engine.addSprite(gamestate.home_team->sprite);
    //  engine.addSprite(gamestate.away_team->sprite);

    // test
    //    ProgressBar bar(40, 3, 50);
    //    gamestate.home_team->getPlayer(0).power_bar = &bar;
    //    engine.addSprite(bar, engine.getDefaultLayer());

    srand(static_cast<unsigned int>(time(nullptr)));

    Joysticker joysticker;
    joysticker.input = &engine.getDefaultGamepad();
    joysticker.team  = gamestate.home_team;
    // joysticker.power_bar = &bar;
    engine.getDefaultGamepad().attachListener(joysticker);

    engine.getMainCamera().setWorldRect(world);

    while (engine.isRunning()) {
        engine.step();
        match.step();
    }
    //    running = false;
    //    for (int i = 0; i < num_threads; ++i) {
    //        threads.at(i).join();
    //    }

    if (argc) {
        std::cout << args[0] << " exited normally" << std::endl;
    }
    return 0;
}
