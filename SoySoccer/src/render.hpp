#pragma once
#include "engine.hpp"
namespace Render {
extern void render_sprites(sf::RenderWindow &window,
                           std::array<Engine::Visualization, Engine::MAX_ENTITIES> &visualizers);
}
