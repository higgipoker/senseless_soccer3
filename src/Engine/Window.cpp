#include "Window.hpp"
namespace Engine {
//
//
//
bool Window::validVideoMode(int width, int height) {
  // get list of supported video modes
  std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

  // search for one that matched the requested width and height
  for (auto &mode : modes) {
    if (mode.width == width && mode.height == height) {
      return true;
    }
  }
  return false;
}
//
//
//
Window::Window(const std::string &title, const int width, const int height,
               int flags, bool fullscreen, const int in_fps) {
  sf::VideoMode video_mode;
  sf::ContextSettings settings;
  video_mode.width = width;
  video_mode.height = height;
  if (fullscreen && validVideoMode(video_mode.width, video_mode.height)) {
    create(video_mode, title, sf::Style::Fullscreen, settings);
  } else {
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    vm.width = width;
    vm.height = height;
    create(vm, title, flags, settings);
  }
  setFramerateLimit(in_fps);
}
}  // namespace Engine
