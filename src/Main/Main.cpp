
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#include "Engine/GameEngine.hpp"
#include "Game/Game.hpp"
#include "Match/Match.hpp"
//
//
//
#include <SFML/System.hpp>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
using namespace Senseless;
//
//
//
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::unique_ptr<Match>      match  = std::make_unique<Match>(wnd_size.width, wnd_size.height, KitFactory::makeDefaultRedKit(), KitFactory::makeDefaultBlueKit());
    std::unique_ptr<GameEngine> engine = std::make_unique<GameEngine>(match->getCamera(), "senseless soccer", wnd_size.width, wnd_size.height);        

    GameState gamestate(*match, match->getHomeTeam(), match->getAwayTeam(), match->getBall(), match->getPitch(), match->getMinimap());
    Entity::gamestate              = &gamestate;
    engine->getDebugUI().gamestate = &gamestate;    

    // add entities to engine
    engine->addEntity(match->getCamera());
    engine->addEntity(match->getPitch(), engine->getBackgroundLayer());
    engine->addEntity(match->getMinimap(), engine->getHudLayer());
    engine->addEntity(match->getBall(), engine->getDefaultLayer());
    for (auto &player : match->getHomeTeam().players) {
        engine->addEntity(*player);
    }
    for (auto &player : match->getAwayTeam().players) {
        engine->addEntity(*player);
    }
    match->getHomeTeam().goToSetPiecePositions(Situation::KickOff);
    
    // main loop
    while (engine->isRunning()) {
        match->step();
        engine->step();
    }
    return 0;
}
