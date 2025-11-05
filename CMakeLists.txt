cmake_minimum_required(VERSION 3.31)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(raylib REQUIRED)
find_package(yaml-cpp REQUIRED)

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
        src/Configs.cpp
        include/Configs.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        yaml-cpp::yaml-cpp
        fmt::fmt
        opengl32
        gdi32
        winmm
)
