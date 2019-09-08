#ifndef NDEBUG
#include "debug.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
//
//
//
void init_debug(sf::RenderWindow &window) { ImGui::SFML::Init(window); }
//
//
//
void shutdown_debug() { ImGui::SFML::Shutdown(); }
//
//
//
void update_debug(sf::RenderWindow &window) {
  ImGui::SFML::Update(window, ui_clock.restart());
  // ImGui::ShowDemoWindow();
  // global debug window
  ImGui::Begin("Debug");

  //
  // draw bounds
  //
  { ImGui::Checkbox("Draw Bounds", &bounds_flag); }

  //
  // grabbed entity
  //
  {
    if (grabbed_entity == NO_ENTITY) {
      ImGui::Text("Grabbed Entity: ");
    } else {
      ImGui::Text("Grabbed Entity: %i", grabbed_entity);
    }
  }

  ImGui::End();
}
//
//
//
void draw_bounds(sf::RenderWindow &window, sf::FloatRect bounds,
                 int highlight) {
  sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
  rect.setPosition(bounds.left, bounds.top);
  rect.setOutlineThickness(1);
  rect.setFillColor(sf::Color::Transparent);
  if (highlight == 1) {
    rect.setOutlineThickness(3);
    rect.setOutlineColor(sf::Color::Green);
  } else if (highlight == 2) {
    rect.setOutlineThickness(3);
    rect.setOutlineColor(sf::Color::Red);
  } else {
    rect.setOutlineColor(sf::Color::White);
  }

  //  const int number_verts = 5;
  //  sf::Vertex vertices[number_verts];
  //  vertices[0].position.x = bounds.left;
  //  vertices[0].position.y = bounds.top;

  //  vertices[1].position.x = bounds.left + bounds.width;
  //  vertices[1].position.y = bounds.top;

  //  vertices[2].position.x = bounds.left + bounds.width;
  //  vertices[2].position.y = bounds.top + bounds.height;

  //  vertices[3].position.x = bounds.left;
  //  vertices[3].position.y = bounds.top + bounds.height;

  //  vertices[4].position.x = bounds.left;
  //  vertices[4].position.y = bounds.top;

  //  for (auto vertex : vertices) {
  //    vertex.color = sf::Color(255, 255, 255, 255);
  //  }
  window.draw(rect);
}
//
//
//
void render_debug(sf::RenderWindow &window) {
  if (bounds_flag) {
    for (int i = 0; i < used_sprite_count; ++i) {
      int status = 0;
      if (hovered_sprites.find(i) != hovered_sprites.end()) {
        status = 1;
      } else if (grabbed_sprite == i) {
        status = 2;
      }
      draw_bounds(window, sprite_pool[i].getGlobalBounds(), status);
    }
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
  grabbed_sprite = entity_pool[grabbed_entity].sprite;
}
//
//
//
void release_entity() {
  grabbed_entity = NO_ENTITY;
  grabbed_sprite = NO_SPRITE;
}
//
//
//
void mouse_dragged(int x, int y) {
  if (grabbed_entity != NO_ENTITY) {
    entity_pool[grabbed_entity].position.x = x + mousegrab_offset.x;
    entity_pool[grabbed_entity].position.y = y + mousegrab_offset.y;
  }
}
//
//
//
void hover_entity(int id) { hovered_sprites.insert(entity_pool[id].sprite); }
//
//
//
void unhover() { hovered_sprites.clear(); }
#endif
