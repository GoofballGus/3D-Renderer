#include "../include/Game.h"


Game::Game() {
    std::cout << "Game on!" << std::endl;
    InitWindow(800, 600, "3D Renderer");
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Render();
    }
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    EndDrawing();
}

void Game::Update() {
    this->Render();
}
