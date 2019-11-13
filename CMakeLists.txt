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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
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

# --------------------------------------------------
# linker flags
# --------------------------------------------------
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# --------------------------------------------------
# build files
# --------------------------------------------------
add_executable(senseless_soccer3
    src/Main/Main.cpp
    src/Engine/Vector.cpp
    src/Engine/Folder.cpp
    src/Engine/Window.cpp
    src/Engine/Movable.cpp
    src/Engine/GameEngine.cpp
    src/Engine/Sprite.cpp
    src/Engine/SpriteAnimation.cpp
    src/Engine/Camera.cpp
    src/Engine/Compass.cpp
    src/Engine/Vector.cpp
    src/Engine/Entity.cpp
    src/Engine/Metrics.cpp
    src/Engine/ArcShape.cpp
    src/Engine/TriangleShape.cpp
    src/Engine/Debug.cpp
    src/Engine/Collider.cpp
    src/Engine/InputDevice.cpp
    src/Engine/Keyboard.cpp
    src/Engine/Gamepad.cpp
    src/Engine/Widget.cpp
    src/Engine/ProgressBar.cpp
    src/Engine/Controllable.cpp
    src/Engine/Texture.cpp
    src/Engine/BaseFactory.cpp
    src/Engine/Picker.cpp
    src/Game/Game.cpp
    src/Locomotion/LocomotionManager.cpp
    src/Locomotion/Locomotion.cpp
    src/Locomotion/Seek.cpp
    src/Locomotion/Head.cpp
    src/Locomotion/Pursue.cpp
    src/Locomotion/Stand.cpp
    src/Brain/Brain.cpp
    src/Brain/BrainState.cpp
    src/Brain/BrainRetrieve.cpp
    src/Brain/BrainDribble.cpp
    src/Brain/BrainPass.cpp
    src/Brain/BrainSupport.cpp
    src/Brain/BrainWait.cpp
    src/Brain/BrainCover.cpp
    src/Player/PlayerFactory.cpp
    src/Player/Player.cpp
    src/Player/PlayerSprite.cpp
    src/Player/PlayerState.cpp
    src/Player/PlayerStateStand.cpp
    src/Player/PlayerStateRun.cpp
    src/Player/PlayerStateDribble.cpp
    src/Pitch/Pitch.cpp
    src/Ball/Ball.cpp
    src/Ball/BallSprite.cpp
    src/Ball/BallFactory.cpp
    src/Match/Match.cpp
    src/Match/MatchFactory.cpp
    src/Team/Team.cpp
    src/Team/PlayingPosition.cpp
    src/Team/PositionDefender.cpp
    src/Team/PositionCenterBack.cpp
    src/Team/PositionFullBack.cpp
    src/Team/PositionMidfielder.cpp
    src/Team/PositionCenterMidfielder.cpp
    src/Team/PositionWideMidfielder.cpp
    src/Team/PositionForward.cpp
    src/Team/PositionCenterForward.cpp
    src/Team/Gameplan.cpp
    src/Team/TeamFactory.cpp
    src/Team/KitFactory.cpp
    src/Controls/Joysticker.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui-SFML.cpp

)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(senseless_soccer3 PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wno-unused-function
    -Wno-unused-parameter
    -Wno-implicit-fallthrough)
endif(CMAKE_COMPILER_IS_GNUCXX)

# --------------------------------------------------
# link libs
# --------------------------------------------------
find_package(OpenGL)
#target_link_libraries (senseless_soccer3 -fsanitize=address)
target_link_libraries (senseless_soccer3 ${OPENGL_gl_LIBRARY})
target_link_libraries (senseless_soccer3 sfml-graphics-d)
target_link_libraries (senseless_soccer3 sfml-window-d)
target_link_libraries (senseless_soccer3 sfml-system-d)
