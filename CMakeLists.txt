cmake_minimum_required(VERSION 3.31)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib/raylib.git
        GIT_TAG 5.0
)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(yaml-cpp)

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
        opengl32
        gdi32
        winmm
)
