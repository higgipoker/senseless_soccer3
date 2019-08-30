cmake_minimum_required(VERSION 2.6)

project(senseless_soccer3)

# --------------------------------------------------
# environment variables
# --------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

# --------------------------------------------------
# include dirs
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
if (WIN32)
    add_definitions(-std:c++latest)
endif (WIN32)

if (UNIX)
    add_definitions(-std=c++17)
endif (UNIX)
#add_definitions(-fsanitize=address)

# --------------------------------------------------
# linker flags
# --------------------------------------------------
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# --------------------------------------------------
# build files
# --------------------------------------------------
add_executable(senseless_soccer3
    src/main.cpp
    src/data.cpp
    src/ball.cpp
    src/player.cpp
    src/input.cpp
    src/texture.cpp
    src/window.cpp
    src/entity.cpp
    src/camera.cpp
    src/animation.cpp
    src/framerate.cpp
    src/game.cpp
    src/grass.cpp
    src/physics.cpp
    src/player_animations.cpp
    src/sprite.cpp
    src/sprite_tools.cpp
    src/gamepad.cpp
    src/keyboard.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui-SFML.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
find_package(OpenGL)
target_link_libraries (senseless_soccer3 ${OPENGL_gl_LIBRARY})
target_link_libraries (senseless_soccer3 gamelib3)
target_link_libraries (senseless_soccer3 sfml-graphics-d)
target_link_libraries (senseless_soccer3 sfml-window-d)
target_link_libraries (senseless_soccer3 sfml-system-d)
