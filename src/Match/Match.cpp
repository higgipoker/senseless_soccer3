#include "Match.hpp"
//
#include "Ball/BallSprite.hpp"
#include "Engine/EntityFactory.h"
#include "Game/Game.hpp"
#include "Team/PositionFactory.h"
#include "Team/Team.hpp"
//
#include <algorithm>
#include <cassert>

namespace Senseless {
//
int Match::instances = 0;
//
//
//
Match::Match(float in_window_width, float in_window_height, const Kit &in_home_kit, const Kit &in_away_kit) : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()) {
    WorkingFolder working_folder;
    Folder        graphics_folder(working_folder.getPath() + "/gfx");

    camera = std::make_unique<Camera>(in_window_width, in_window_height);
    camera->name = "Match Camera";
    camera->getHudView().setSize(in_window_width, in_window_height);
    camera->getHudView().setCenter(in_window_width / 2, in_window_height / 2);
    camera->setWorldRect(world);

    // texture for home team
    Texture home_texture;
    home_texture.loadFromFile(PlayerFactory::getSpriteSheeet(in_home_kit.type));
    home_texture.swapColors(in_home_kit.palette);

    // texture for away team
    Texture away_texture;
    away_texture.loadFromFile(PlayerFactory::getSpriteSheeet(in_away_kit.type));
    away_texture.swapColors(in_away_kit.palette);

    // shadow texture
    Texture shadow_texture;
    shadow_texture.loadFromFile(PlayerFactory::getShadowSheet());

    // ball texture
    BallFactory ball_factory;
    Texture     ball_texture;
    ball_texture.loadFromFile(ball_factory.getSpriteSheeet(BallType::Standard));

    // so that we are not constantly switching context to render each entity, they all share the same "mega texture" created here
    auto width = std::max(home_texture.getSize().x, std::max(away_texture.getSize().x, std::max(shadow_texture.getSize().x, ball_texture.getSize().x)));

    auto height = home_texture.getSize().y + away_texture.getSize().y + shadow_texture.getSize().y + ball_texture.getSize().y;

    match_texture = std::make_unique<sf::RenderTexture>();
    if (!match_texture->create(width, height)) {
        std::cout << "Could not create tecture with dimensions " << width << "x" << height << std::endl;
        std::cout << "Max texture dimensions: " << sf::Texture::getMaximumSize() << " x " << sf::Texture::getMaximumSize() << std::endl;
        assert(false);
    }

    sf::Sprite s1(home_texture);
    sf::Sprite s2(away_texture);
    sf::Sprite s3(shadow_texture);
    sf::Sprite s4(ball_texture);
    s2.move(0, s1.getLocalBounds().height);
    s3.move(0, s2.getGlobalBounds().top + s2.getLocalBounds().height);
    s4.move(0, s3.getGlobalBounds().top + s3.getLocalBounds().height);

    match_texture->clear({0, 0, 0, 0});
    match_texture->draw(s1);
    match_texture->draw(s2);
    match_texture->draw(s3);
    match_texture->draw(s4);
    match_texture->display();

    auto shadow = std::make_unique<BallShadowSprite>(match_texture->getTexture());
    auto sprite = std::make_unique<BallSprite>(match_texture->getTexture());
    ball        = std::make_unique<Ball>(std::move(sprite), std::move(shadow));
    home_team   = std::make_unique<Team>("Home Team");
    away_team   = std::make_unique<Team>("Away Team");
    pitch       = std::make_unique<Pitch>(graphics_folder.getPath(true) + "grass_checked.png");
    minimap     = std::make_unique<MiniMap>(*home_team, *away_team, *ball, *pitch, *camera);
    camera->setHeight(50);
    minimap->movable.position = {10, 10};

    ball->movable.position   = pitch->toScreenSpace({pitch->getDimensions().center_spot.getCenter().x, pitch->getDimensions().center_spot.getCenter().y});
    ball->movable.position.z = 50;
    camera->follow(*ball);

    home_team->attacking_goal = (Direction::North);
    home_team->defending_goal = (Direction::South);
    home_team->gameplan.defensive_line_height = DefensiveLineType::Normal;
    home_team->gameplan.defensive_width_type  = DefensivewidthType::Normal;
    home_team->setAttackingState(AttackingState::Attacking);

    away_team->attacking_goal = (Direction::South);
    away_team->defending_goal = (Direction::North);
    away_team->gameplan.defensive_line_height = DefensiveLineType::Normal;
    away_team->gameplan.defensive_width_type  = DefensivewidthType::Normal;
    away_team->setAttackingState(AttackingState::Defending);

    // test add a player to the home team
    PositionFactory positions;
    auto            right_center_forward = positions.newCenterForward(*pitch, *home_team, *away_team);
    right_center_forward->applyModifier(PositionModifier::Right);
    right_center_forward->name = "Right Center Forward";
    Player &player             = newPlayer(TeamStrip::Home);
    player.name                = right_center_forward->name;
    player.setPlayingPosition(std::move(right_center_forward));
    player.movable.position = pitch->toScreenSpace({0, pitch->getDimensions().halfway_line.getPosition().y});
    player.my_team          = home_team.get();
    player.other_team       = away_team.get();

    home_team->addPlayer(&player);

    ++instances;
    // std::cout << instances << " matches" << std::endl;
}
//
//
//
Match::~Match() {
    --instances;
    // std::cout << instances << " matches" << std::endl;
}
//
//
//
Player &Match::newPlayer(const TeamStrip in_strip) {
    auto shadow = std::make_unique<PlayerShadowSprite>(match_texture->getTexture());
    auto sprite = std::make_unique<PlayerSprite>(match_texture->getTexture(), in_strip);
    auto player = std::make_unique<Player>(std::move(sprite), std::move(shadow));
    players.emplace_back(std::move(player));
    return *players.back();
}
//
//
//
const sf::Texture &Match::getMatchTexture() {
    return match_texture->getTexture();
}
//
//
//
void Match::step() {
}

//
//
//
void Match::setAttackingTeam(const TeamStrip in_which) {
    auto attacking_team = in_which;
    switch (attacking_team) {
        case TeamStrip::Home:
            gamestate->home_team->setAttackingState(AttackingState::Attacking);
            gamestate->away_team->setAttackingState(AttackingState::Defending);
            break;
        case TeamStrip::Away:
            gamestate->home_team->setAttackingState(AttackingState::Defending);
            gamestate->away_team->setAttackingState(AttackingState::Attacking);
            break;
    }
}
}  // namespace Senseless
