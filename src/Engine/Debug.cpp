#include "Debug.hpp"

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
namespace Engine {
//
//
//
Debug::Debug(sf::RenderWindow &in_window) : window(in_window) {
  ImGui::SFML::Init(in_window);
}
//
//
//
Debug::~Debug() { ImGui::SFML::Shutdown(); }
//
//
//
void Debug::update() {
  ImGui::SFML::Update(window, ui_clock.restart());
  //ImGui::ShowDemoWindow();
  ImGui::Begin("Debug");


  { ImGui::Checkbox("Draw Bounds", &flag_draw_bounds); }
  ImGui::End();
  ImGui::SFML::Render(window);
}
//
//
//
void Debug::pollEvent(sf::Event &in_event){
  ImGui::SFML::ProcessEvent(in_event);
}
}  // namespace Engine
