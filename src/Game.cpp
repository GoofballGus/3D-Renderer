#include "../include/Game.h"

#include <iomanip>


void LogColored(int msgType, const char *text, va_list args) {
    switch (msgType)
    {
        case LOG_INFO:
            printf("\033[0;38;2;91;149;41;49m[INFO]\033[0m : ");
            break;
        case LOG_ERROR:
            printf("\033[0;38;2;216;82;75;49m[ERROR]\033[0m : ");
            break;
        case LOG_WARNING:
            printf("\033[0;38;2;165;137;14;49m[WARNING]\033[0m : ");
            break;
        case LOG_FATAL:
            printf("\033[1;31;49m[FATAL]\033[0m : ");
            break;
        case LOG_DEBUG: printf("\033[0;38;2;0;206;209;49m[DEBUG]\033[0m : "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}


Game::Game() {}

Game::~Game() {}

void Game::init() {
    InitWindow(1280, 720, "3D Renderer");

    if (!IsWindowReady()) {
        std::cerr << "[ERROR] Failed to initialize window." << std::endl;
    }

    SetTargetFPS(FPS);

    SetTraceLogCallback(LogColored);

    // Load textures and materials
    assets.Setup();

    // init world & player
    world.generateDefaultTerrain(assets);

    shader = LoadShader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    running = true;

    DisableCursor();
    // SetExitKey(KEY_NULL);
}

void Game::run() {
    while (running && !WindowShouldClose()) {
        float dt = GetFrameTime();
        update(dt);
        render();
    }
}

void Game::update(float dt) {
    player.update(dt, world);
    world.update(dt);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode3D(*player.getCamera());
    // BeginShaderMode(shader);

    // rlEnableBackfaceCulling();

    DrawGrid(1000, 1);
    world.render(assets);
    // player.renderHands();

    // EndShaderMode();
    EndMode3D();

    DrawFPS(3, 0);

    if (IsKeyPressed(KEY_F3)) {
        f3 = !f3;
    }

    if (f3 == true) {
        debugRender();
    }

    EndDrawing();
}

void Game::debugRender() const {
    int positionAccuracy = 3;
    std::ostringstream playerPosX;
    playerPosX << std::fixed << "Player X: " << std::setprecision(positionAccuracy) << player.position.x;
    std::string playerPosXString = playerPosX.str();
    DrawText(playerPosXString.c_str(), 10, 30, 20, DARKGRAY);

    std::ostringstream playerPosY;
    playerPosY << std::fixed << "Player Y: " << std::setprecision(positionAccuracy) << player.position.y;
    std::string playerPosYString = playerPosY.str();
    DrawText(playerPosYString.c_str(), 10, 50, 20, DARKGRAY);

    std::ostringstream playerPosZ;
    playerPosZ << std::fixed << "Player Z: " << std::setprecision(positionAccuracy) << player.position.z;
    std::string playerPosZString = playerPosZ.str();
    DrawText(playerPosZString.c_str(), 10, 70, 20, DARKGRAY);

    DrawText(std::to_string(player.horizontalVelocity.x).c_str(), 250, 30, 20, DARKGRAY);
    DrawText(std::to_string(player.horizontalVelocity.y).c_str(), 250, 50, 20, DARKGRAY);
    DrawText(std::to_string(player.verticalVelocity).c_str(), 250, 70, 20, DARKGRAY);
}

void Game::shutdown() {
    if (!running) return;

    running = false;

    TraceLog(LOG_INFO, "[SHUTDOWN] Unloading materials");
    assets.materials.UnloadAll();
    TraceLog(LOG_INFO, "[SHUTDOWN] Unloaded materials");

    TraceLog(LOG_INFO, "[SHUTDOWN] Unloading textures");
    assets.textures.UnloadAll();
    TraceLog(LOG_INFO, "[SHUTDOWN] Unloaded textures");

    TraceLog(LOG_INFO, "[SHUTDOWN] Unloading shader");
    UnloadShader(shader);
    TraceLog(LOG_INFO, "[SHUTDOWN] Unloaded shader");

    TraceLog(LOG_ALL, "[SHUTDOWN] Successful shutdown!");

    CloseWindow();
}
