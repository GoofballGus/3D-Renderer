#include "Game.h"


Game::Game() {
    std::cout << "Game on!" << std::endl;
    InitWindow(800, 600, "3D Renderer");
    SetWindowFocused();

    DisableCursor();

    Camera3D camera = {};
    camera.position = (Vector3){2.0f, 2.0f, 2.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, -2.0f}; // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    camera.fovy = 45.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    this->camera = camera;

    this->assetManager.LoadAssets();
    this->blockManager = BlockManager(&assetManager);

    // SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}


Game::~Game() {
    blockManager->UnloadBlocks();
    assetManager.UnloadAssets();
}


void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Render();
    }
}


void Game::Render() {
    // Y-up right-handed rendering
    // Z- north
    // Z+ south
    // Y+ up
    // Y- down
    // X+ east
    // X- west

    BeginDrawing();
    BeginMode3D(this->camera);
    ClearBackground(RAYWHITE);

    DrawGrid(100, 1);

    DrawModel(
        *blockManager->GetBlock(BlockType::BLOCK_EXAMPLE)->model,
        {0,0,0},
        1.0f,
        WHITE
        );

    EndMode3D();

    DrawFPS(10, 10);

    DrawText(("X: " + std::to_string(camera.position.x)).c_str(), 10, 30, 10, BLACK);
    DrawText(("Y: " + std::to_string(camera.position.y)).c_str(), 10, 40, 10, BLACK);
    DrawText(("Z: " + std::to_string(camera.position.z)).c_str(), 10, 50, 10, BLACK);

    EndDrawing();
}


void Game::Update() {
    // Camera movement
    float speed = 10.0f;
    float delta = GetFrameTime();
    float mouseSensitivity = 0.15f;

    // Mouse look
    Vector2 mouseDelta = GetMouseDelta();

    UpdateCameraPro(&camera,
        (Vector3){
            (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*speed*delta - (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*speed*delta,
            (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*speed*delta - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*speed*delta,
            (IsKeyDown(KEY_SPACE)*speed*delta - IsKeyDown(KEY_LEFT_SHIFT)*speed*delta)
        },
        (Vector3){
            mouseDelta.x * mouseSensitivity,  // Rotation: yaw (left-right)
            mouseDelta.y * mouseSensitivity,  // Rotation: pitch (up-down)
            0.0f                               // Rotation: roll
        },
        0.0f);  // Field of view change (zoom)
}
