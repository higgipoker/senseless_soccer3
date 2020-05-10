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
namespace Senseless {
//
class Match;
class Team;
enum class KitType;
enum class TeamType;
//
//
//
class PlayerFactory : public BaseFactory {
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
    UniquePtr<Player> makePlayer(Match &        in_match,
                                 const Team &   in_my_team,
                                 const Team &   in_other_team,
                                 const TeamType in_strip);
};
}  // namespace Senseless
