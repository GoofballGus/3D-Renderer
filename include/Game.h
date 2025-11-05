#pragma once
#include "AssetManager.h"
#include "Player.h"
#include "World.h"
#include "raylib.h"
#include "rlgl.h"
#include <iostream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <iomanip>

class Game {
public:
    Game();                      // no args — Game owns Player/World
    ~Game();                     // calls shutdown internally

    void init();                 // load assets, init player/world
    void run();                  // main loop (update+render until close)
    void shutdown();
private:
    void update(float dt);
    void render();
    void debugRender() const;

    AssetManager assets;
    Player player;
    World world{5, 1, 5};
    Shader shader;
    Mesh mesh;
    Model model;

    bool f3 = false;
    int FPS = 60;
    bool running = false;
};
