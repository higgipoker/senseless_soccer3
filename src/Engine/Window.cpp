#include "Window.hpp"
#include "Folder.hpp"
namespace Senseless {
//
//
//
bool Window::validVideoMode(unsigned int width, unsigned int height) {
    // search for one that matched the requested width and height
    for (auto &mode : sf::VideoMode::getFullscreenModes()) {
        if (mode.width == width && mode.height == height) {
            return true;
        }
    }
    return false;
}
//
//
//
Window::Window(const std::string &title, const int width, const int height, int flags, bool fullscreen,
               const int in_fps) {
    sf::VideoMode video_mode;
    sf::ContextSettings settings;
    video_mode.width = width;
    video_mode.height = height;
    if (fullscreen && validVideoMode(video_mode.width, video_mode.height)) {
        create(video_mode, title, sf::Style::Fullscreen, settings);
    } else {
        video_mode = sf::VideoMode::getDesktopMode();
        video_mode.width = width;
        video_mode.height = height;
        create(video_mode, title, flags, settings);
    }
    setFramerateLimit(in_fps);

    // tmp hard coded
    WorkingFolder folder;
    sf::Image icon;
    icon.loadFromFile(folder.getPath(true) + "gfx/icon.png");
    setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
}  // namespace Senseless
