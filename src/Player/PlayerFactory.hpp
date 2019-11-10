#pragma once
#include "Player.hpp"
//
#include "Team/KitFactory.hpp"
//
#include "Engine/BaseFactory.hpp"
#include "Engine/Folder.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Types.hpp"
//
#include <SFML/Graphics/Texture.hpp>
//
class Match;
class Team;
enum class KitType;
enum class TeamType;
//
//
//
class PlayerFactory : public Engine::BaseFactory {
   public:
    //
    //
    //
    std::string getSpriteSheeet(const KitType in_kit_type) {
        switch (in_kit_type) {
            case KitType::Standard:
                return graphics_folder.getPath(true) + "player.png";
                break;
        }

        return graphics_folder.getPath(true) + "player.png";
    }
    //
    //
    //
    std::string getShadowSheet() {
        return graphics_folder.getPath(true) + "player_shadow.png";
    }
    //
    //
    //
    UniquePtr<Player> makePlayer(Match & in_match, Team &in_Team, const TeamType in_strip);
};
