#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "AssetManager.h"
#include "BlockManager.h"
#include "raylib.h"
#include "raymath.h"
#include <optional>

class Game {
public:
    Game();
    ~Game();

    void Run();
private:
    void Update();
    void Render();

    Camera3D camera = Camera3D();
    AssetManager assetManager;
    std::optional<BlockManager> blockManager;
};

#endif //GAME_H
