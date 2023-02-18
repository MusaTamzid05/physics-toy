# This is the CMakeLists.txt file of the "hello world" project
# in order to show a simple executable that uses the ReactPhysics3D library

# Minimum cmake version required
cmake_minimum_required(VERSION 3.8)

set(CMAKE_BUILD_TYPE Debug)

set(
    SOURCE_FILES
    src/main.cpp
    src/shader.cpp
    src/game_object.cpp
    src/camera.cpp
    src/scene.cpp
    src/utils.cpp

    src/cube.cpp
    src/plane.cpp

    src/cyclone/particle.cpp


    src/texture_manager.cpp

    src/demos/simple_scene.cpp

    )

# Project
project(game_engine)

include_directories(include)

# Create the executable
add_executable(engine ${SOURCE_FILES})

# Link with the ReactPhysics3D library
target_link_libraries(engine sfml-graphics sfml-window sfml-system GL GLEW)
