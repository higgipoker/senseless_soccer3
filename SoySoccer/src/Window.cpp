#include "Window.hpp"
#include "Folder.hpp"
namespace SoySoccer {
//
//
//
bool Window::valid_video_mode(unsigned int width, unsigned int height) {
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
               const int in_fps)
    : hud(*this) {
    sf::VideoMode video_mode;
    sf::ContextSettings settings;
    video_mode.width = width;
    video_mode.height = height;
    if (fullscreen && valid_video_mode(video_mode.width, video_mode.height)) {
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
//
//
//
void Window::Update() {
    if (hasFocus()) {
        sf::Event event;
        while (pollEvent(event)) {
            hud.HandleInput(event);
            switch (event.type) {
                case sf::Event::Closed:
                    close();
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Escape) {
                        if (hud.shown) {
                            hud.shown = !hud.shown;
                        } else {
                            close();
                        }
                    } else if (event.key.code == sf::Keyboard::Tab) {
                        hud.shown = !hud.shown;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    this->clear(sf::Color::Green);
    hud.Show();
    this->display();
}
}  // namespace SoySoccer
