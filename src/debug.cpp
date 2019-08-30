#include "debug.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void init_debug(sf::RenderWindow &window) { ImGui::SFML::Init(window); }
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void clean_debug() { ImGui::SFML::Shutdown(); }
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void update_debug(sf::RenderWindow &window) {
  ImGui::SFML::Update(window, ui_clock.restart());
  // ImGui::ShowDemoWindow();
  // global debug window
  ImGui::Begin("Debug");
  ImGui::End();
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void draw_bounds(sf::RenderWindow &window, sf::FloatRect bounds) {
  const int number_verts = 5;
  sf::Vertex vertices[number_verts];
  vertices[0].position.x = bounds.left;
  vertices[0].position.y = bounds.top;

  vertices[1].position.x = bounds.left + bounds.width;
  vertices[1].position.y = bounds.top;

  vertices[2].position.x = bounds.left + bounds.width;
  vertices[2].position.y = bounds.top + bounds.height;

  vertices[3].position.x = bounds.left;
  vertices[3].position.y = bounds.top + bounds.height;

  vertices[4].position.x = bounds.left;
  vertices[4].position.y = bounds.top;

  for (auto vertex : vertices) {
    vertex.color = sf::Color(255, 255, 255, 255);
  }
  window.draw(vertices, number_verts, sf::LinesStrip);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void render_debug(sf::RenderWindow &window) {
  for (int i = 0; i < used_sprite_count; ++i) {
    draw_bounds(window, sprite_pool[i].getGlobalBounds());
  }
  ImGui::SFML::Render(window);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void toggle_debug() { pending_debug_toggle = !pending_debug_toggle; }