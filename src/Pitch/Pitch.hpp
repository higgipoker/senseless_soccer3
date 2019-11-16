#pragma once
#include "MiniMap.hpp"
#include "PitchSprite.hpp"
#include "PitchTypes.hpp"
//
#include "Engine/Entity.hpp"
//
//
//
class Pitch : public Engine::Entity {
   public:
    //
    //
    //
    Pitch(const std::string &in_grass_texture, const sf::FloatRect in_bounds);
    //
    //
    //
    void update();
    //
    //
    //
    Engine::Sprite &getSprite();
    //
    //
    //
    Engine::Sprite &getMiniMap();
    //
    //
    //
    Engine::Vector3 toScreenSpace(const Engine::Vector3 &in_vector) const;
    //
    //
    //
    Engine::Vector3 toPitchSpace(const Engine::Vector3 &in_vector) const;
    //
    //
    //
    const PitchDimensions &getDimensions() const {
        return dimensions;
    }
    //
    //
    //
    Engine::Entity &getMiniMapEntity(){
        return minimap_entity;
    }

   private:
    PitchDimensions dimensions;
    PitchSprite sprite;
    UniquePtr<Engine::Sprite> minimap {std::make_unique<MiniMap>()};
    Engine::Entity minimap_entity;
    //
    //
    //
    void init_bounds();
    //
    //
    //
    void init_6_yard_boxes();
    //
    //
    //
    void init_18_yard_boxes();
    //
    //
    //
    void init_center_circle();
    //
    //
    //
    void init_center_spot();
    //
    //
    //
    void init_penalty_spots();
    //
    //
    //
    void init_north_arc();
    //
    //
    //
    void init_halfway_line();
};
