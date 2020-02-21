cmake_minimum_required(VERSION 3.5)

project(SoySoccer LANGUAGES CXX)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
if (WIN32)
    add_definitions(-std:c++latest)
endif (WIN32)

if (UNIX)
    add_definitions(-std=c++17)
endif (UNIX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# include dirs
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(SoySoccer
    src/main.cpp
    src/Engine.cpp
    src/Controllable.cpp
    src/Movable.cpp
    src/Renderable.cpp
    src/Animation.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui-SFML.cpp
    src/ImGuiHud.cpp
    src/input.cpp
    src/render.cpp
    src/Folder.cpp
    src/Window.cpp
    src/Texture.cpp
    src/Sprite.cpp
    src/SpriteAnimation.cpp
    src/Entity.cpp
    src/Simulate.cpp
    src/Player.cpp
    src/Ball.cpp
    src/Vector.cpp
    src/Math.cpp
    src/Visualize.cpp
    src/Interact.cpp
    src/SpriteSheet.cpp
    )

# --------------------------------------------------
# link libs
# --------------------------------------------------
find_package(OpenGL)
target_link_libraries (SoySoccer -pthread)
target_link_libraries (SoySoccer ${OPENGL_gl_LIBRARY})
target_link_libraries (SoySoccer sfml-graphics-d)
target_link_libraries (SoySoccer sfml-window-d)
target_link_libraries (SoySoccer sfml-system-d)
