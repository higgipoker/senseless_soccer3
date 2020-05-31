#pragma once
#include "Player.hpp"
//
#include "Team/KitFactory.hpp"
//
#include "Engine/BaseFactory.hpp"
#include "Engine/Folder.hpp"
#include "Engine/Texture.hpp"
#include <memory>
//
#include <SFML/Graphics/Texture.hpp>
namespace Senseless {
//
class Match;
class Team;
enum class KitType;
enum class TeamStrip;
//
//
//
class PlayerFactory : public BaseFactory {
   public:
    //
    //
    //
    static std::string getSpriteSheeet(const KitType in_kit_type) {
        switch (in_kit_type) {
            case KitType::Standard:
                return working_folder.getPath() + "/gfx/" + "player.png";
                break;
        }

        return working_folder.getPath() + "/gfx/" + "player.png";
    }
    //
    //
    //
    static std::string getShadowSheet() {
        return working_folder.getPath() + "/gfx/" + "player_shadow.png";
    }
};
}  // namespace Senseless
