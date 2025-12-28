cmake_minimum_required(VERSION 3.31)
project(3DRenderer VERSION 1.0.0 LANGUAGES CXX)

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
FetchContent_MakeAvailable(raylib)

# Main executable with all your source files
add_executable(3DRenderer
        src/main.cpp
        src/Game.cpp
        include/Game.h
        include/main.h
)

target_include_directories(3DRenderer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(3DRenderer
        PRIVATE
        raylib
)
