
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
enum class GameState { Main_Menu, Load_Match, Match, Unload_Match };
bool      loadMatch();
bool      unloadMatch();
GameState doMainMenu(void);

GameEngine engine("senseless soccer", wnd_size.width, wnd_size.height);
std::unique_ptr<Match> match;
//
//
//
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));



    // main loop
    GameState state = GameState::Main_Menu;
    while (engine.isRunning()) {
        switch (state) {
            case GameState::Main_Menu:
                state = doMainMenu();
                break;
            case GameState::Load_Match:
                match = std::make_unique<Match>(wnd_size.width, wnd_size.height, KitFactory::makeDefaultRedKit(), KitFactory::makeDefaultBlueKit());
                if (loadMatch()) {
                    state = GameState::Match;
                } else {
                    // oops
                }
                break;
            case GameState::Match:
                match->step();
                if (match->finished()) {
                    state = GameState::Unload_Match;
                }
                break;

            case GameState::Unload_Match:
                if (unloadMatch()) {
                    match.reset();
                    state = GameState::Main_Menu;
                } else {
                    // oops
                }
                break;
        }
        engine.step();
    }
    return 0;
}
//
//
//
GameState doMainMenu() {
    GameState state = GameState::Main_Menu;
    while (state == GameState::Main_Menu) {
        state = GameState::Load_Match;
    }
    // this would be something selected from the menu
    return state;
}
//
//
//
bool loadMatch() {    
    Entity::match             = match.get();
    engine.getDebugUI().match = match.get();

    // add entities to engine
    engine.addCamera(match->getCamera());
    engine.addEntity(match->getPitch(), engine.getBackgroundLayer());
    engine.addEntity(match->getMinimap(), engine.getHudLayer());
    engine.addEntity(match->getBall(), engine.getDefaultLayer());
    for (auto &player : match->getHomeTeam().players) {
        engine.addEntity(*player);
    }
    for (auto &player : match->getAwayTeam().players) {
        engine.addEntity(*player);
    }
    match->getHomeTeam().goToSetPiecePositions(Situation::KickOff);
    Player::match = match.get();
    return true;
}
//
//
//
bool unloadMatch() {
    std::cout << std::endl;
    engine.reset();    
    return true;
}
