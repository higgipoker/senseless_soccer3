#include "window.hpp"

// -----------------------------------------------------------------------------
// valid_videomode
// -----------------------------------------------------------------------------
bool valid_videomode(int width, int height) {
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

// -----------------------------------------------------------------------------
// init_window
// -----------------------------------------------------------------------------
void init_window(sf::RenderWindow &window, const std::string &title,
                 const int width, const int height, int flags,
                 bool fullscreen) {
  sf::VideoMode video_mode;
  video_mode.width = width;
  video_mode.height = height;
  if (fullscreen && valid_videomode(video_mode.width, video_mode.height)) {
    window.create(video_mode, title, sf::Style::Fullscreen);
  } else {
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    vm.width = width;
    vm.height = height;
    window.create(vm, title, flags);
  }
  window.setVerticalSyncEnabled(true);
  //window.setFramerateLimit(60);
}