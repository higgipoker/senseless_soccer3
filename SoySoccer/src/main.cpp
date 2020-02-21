#include "Ball.hpp"
#include "Folder.hpp"
#include "Player.hpp"
#include "SpriteSheet.hpp"
#include "Texture.hpp"
#include "Engine.hpp"
#include "Window.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <array>
#include <iostream>

static WorkingFolder folder;
using namespace std;
//
//
//
static const SpriteSheet player_spritesheet = {"player.png", 32, 32, 1, 0, 0, 1, 0};
static const SpriteSheet ball_spritesheet = {"ball.png", 32, 32, 7, 0, 0, 7, 64};
//
//
//
//void init_sprite(sf::Sprite &sprite, const sf::Texture &texture, const SpriteSheet &spritesheet) {
//    sprite.setTexture(texture);
//    std::vector<sf::IntRect> frames;
//    int x = spritesheet.frame_width * spritesheet.start_col;
//    int y = spritesheet.vertical_offset + spritesheet.frame_height * spritesheet.start_row;
//    int col = spritesheet.start_col;
//    int frame_count = spritesheet.spriteset_frames;
//    while (--frame_count >= 0) {
//        sf::IntRect rect;
//        rect.left = x;
//        rect.top = y;
//        rect.width = spritesheet.frame_width;
//        rect.height = spritesheet.frame_height;
//        frames.push_back(rect);

//        // next col
//        x += spritesheet.frame_width;

//        // next row
//        if (++col == spritesheet.sheet_cols) {
//            x = 0;
//            y += spritesheet.frame_height;
//            col = 0;
//        }
//    }
//    sprite.setTextureRect(frames.at(0));

//    // default set origin to center
//    sprite.setOrigin(
//        {static_cast<float>(spritesheet.frame_width / 2), static_cast<float>(spritesheet.frame_height / 2)});
//}
//
//
//
int main() {
    SoySoccer::Window window("SoySoccer", 800,600, sf::Style::Default);
    while(window.isOpen()){
        window.Update();
    }

//    //
//    // players
//    //
//    constexpr int num_players = 22;
//    std::array<Player, num_players> players;
//    sf::Texture player_texture, player_texture2, ball_texture;
//    player_texture.loadFromFile((folder.getPath() + "/gfx/" + player_spritesheet.filename));
//    player_texture2.loadFromFile((folder.getPath() + "/gfx/" + player_spritesheet.filename));
//    std::vector<std::pair<sf::Color, sf::Color> > palette = {{{255, 0, 0, 255}, {0, 0, 255, 255}}};
//    Texture::changeColors(player_texture2, palette);

//    ball_texture.loadFromFile((folder.getPath() + "/gfx/" + ball_spritesheet.filename));
//    Texture merged_texture;

//    if (merged_texture.merge({&player_texture, &player_texture2, &ball_texture}) == false) {
//        return 1;
//    }
//    merged_texture.get().copyToImage().saveToFile(folder.getPath() + "/tmp.png");
//    for (int i = 0; i < num_players; ++i) {
//        players.at(i).id = Engine::reserve_entity(game.engine);
//        init_sprite(game.engine.visualizers[players.at(i).id], merged_texture.get(), player_spritesheet);
//        game.engine.simulations.at(players.at(i).id).position = {200, 200};
//    }

//    //
//    // ball
//    //
//    Ball ball;
//    ball.id = Engine::reserve_entity(game.engine);
//    init_sprite(game.engine.visualizers[ball.id], merged_texture.get(), ball_spritesheet);
//    game.engine.simulations.at(ball.id).position = {200, 200};
//    game.engine.visualizers.at(ball.id).scale(0.5f, 0.5f);

//    Hud::init(game.window);

//    while (game.window.isOpen()) {
//        for (auto &player : players) {
//            update_player(player, game.engine);
//        }
//        sf::Event event;
//        while (game.window.pollEvent(event)) {
//            if (game.window.hasFocus()) {
//                Hud::on_interact(game.hud, event);
//                switch (event.type) {
//                    case sf::Event::Closed:
//                        game.window.close();
//                        break;
//                    case sf::Event::KeyReleased:
//                        if (event.key.code == sf::Keyboard::Escape) {
//                            if (game.hud.shown) {
//                                game.hud.shown = !game.hud.shown;
//                            } else {
//                                game.window.close();
//                            }
//                        } else if (event.key.code == sf::Keyboard::Tab) {
//                            game.hud.shown = !game.hud.shown;
//                        }
//                        break;
//                    default:
//                        break;
//                }
//            }
//        }
//        // Engine::interact(game.engine, game.window);
//        Engine::simulate(game.engine);
//        game.window.clear(sf::Color::Green);
//        Engine::visualize(game.engine, game.window);
//        Hud::show(game.hud, game.window);
//        game.window.display();
//    }
//    Hud::cleanup();

    return 0;
}
