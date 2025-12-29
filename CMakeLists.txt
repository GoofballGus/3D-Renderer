cmake_minimum_required(VERSION 3.31)
project(3DRenderer VERSION 1.0.0 LANGUAGES CXX)

add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch Raylib
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.9.7
)
FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(magic_enum)

# Main executable with all your source files
add_executable(3DRenderer
        src/main.cpp
        src/Game.cpp
        include/Game.h
        include/main.h
        src/AssetManager.cpp
        include/AssetManager.h
        include/BlockType.h
        include/ItemType.h
        include/BlockModel.h
        src/BlockManager.cpp
        include/BlockManager.h
        include/Block.h
)

target_include_directories(3DRenderer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(3DRenderer
        PRIVATE
        raylib
        magic_enum
)
