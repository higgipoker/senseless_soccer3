#include "debug.hpp"
//
//
//
void init_debug(sf::RenderWindow &window) { ImGui::SFML::Init(window); }
//
//
//
void clean_debug() { ImGui::SFML::Shutdown(); }
//
//
//
void update_debug(sf::RenderWindow &window) {
  ImGui::SFML::Update(window, ui_clock.restart());
  // ImGui::ShowDemoWindow();
  // global debug window
  ImGui::Begin("Debug");
  ImGui::Text("Grabbed Entity: %i", grabbed_entity);
  ImGui::End();
}
//
//
//
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
//
//
//
void render_debug(sf::RenderWindow &window) {
  for (int i = 0; i < used_sprite_count; ++i) {
    draw_bounds(window, sprite_pool[i].getGlobalBounds());
  }
  for (auto &shape : debug_shapes) {
    window.draw(*shape);
  }
  debug_shapes.clear();
  ImGui::SFML::Render(window);
}
//
//
//
void toggle_debug() { pending_debug_toggle = !pending_debug_toggle; }
//
//
//
void grab_entity(int id, int mouse_x, int mouse_y) {
  grabbed_entity = id;
  sf::Vector2f center{entity_pool[id].position.x, entity_pool[id].position.y};
  sf::Vector2f mouse{static_cast<float>(mouse_x), static_cast<float>(mouse_y)};
  mousegrab_offset = center - mouse;
}
//
//
//
void release_entity() { grabbed_entity = NO_ENTITY; }
//
//
//
void mouse_dragged(int x, int y) {
  if (grabbed_entity != NO_ENTITY) {
    entity_pool[grabbed_entity].position.x = x + mousegrab_offset.x;
    entity_pool[grabbed_entity].position.y = y + mousegrab_offset.y;
  }
}
