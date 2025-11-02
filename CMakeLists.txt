cmake_minimum_required(VERSION 3.31)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

# Use FetchContent to grab raylib
include(FetchContent)

FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)

# Make raylib available
FetchContent_MakeAvailable(raylib)

add_executable(3DRenderer
        main.cpp
        include/main.h
        src/Player.cpp
        include/Player.h
        src/AssetManager.cpp
        include/AssetManager.h
        src/Game.cpp
        include/Game.h
        src/World.cpp
        include/World.h
        src/Block.cpp
        include/Block.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        opengl32
        gdi32
        winmm
)
