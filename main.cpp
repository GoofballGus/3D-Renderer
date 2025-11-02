#include "include/Game.h"


constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

float sensitivity = 0.2f;
float playerSpeed = 5.0f;

constexpr int CHUNK_SIZE = 16;

int main() {
    Game game;

    game.init();
    game.run();

    game.shutdown();


    // TraceLog(LOG_INFO, "Loading the shader");
    // Shader shader = LoadShader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
    // if (shader.id == 0) {
    //     std::cerr << "Failed to load shader." << std::endl;
    //     CloseWindow();
    //     return 1;
    // }
    // int locViewPos = GetShaderLocation(shader, "viewPos");
    //
    //
    // Mesh blockMesh = CreateCubeMesh(1.0f);
    // TraceLog(LOG_INFO, "[DEBUG] Created block mesh");
    // Model blockModel = LoadModelFromMesh(blockMesh);
    // TraceLog(LOG_INFO, "[DEBUG] Created block model from mesh");
    //
    // Chunk chunk(&blockMesh, &blockModel, {0, 0, 0}, textureManager);
    // TraceLog(LOG_INFO, "[DEBUG] Made Chunk");
    // chunk.setBlock(1, 1, 1 , static_cast<short>(textureManager.getBlockIdFromName("broken")));
    // chunk.setBlock(8, 0, 8 , static_cast<short>(textureManager.getBlockIdFromName("test")));
    // chunk.setBlock(2, 1, 8 , static_cast<short>(textureManager.getBlockIdFromName("stone")));
    // chunk.setBlock(8, 1, 2 , static_cast<short>(textureManager.getBlockIdFromName("dirt")));
    // chunk.setBlock(0, 2, 0, static_cast<short>(textureManager.getBlockIdFromName("test")));
    // chunk.setBlock(0, 0, 0, static_cast<short>(textureManager.getBlockIdFromName("dirt")));
    // TraceLog(LOG_INFO, "[DEBUG] Placed blocks");
    //
    // DisableCursor();
    // SetTargetFPS(60);
    // // TODO(): Turn on SetExitKey(KEY_NULL) after debugging!
    // // SetExitKey(KEY_NULL);
    //
    // while (!WindowShouldClose()) {
    //     if (IsKeyPressed(KEY_ESCAPE) and IsCursorHidden()) {
    //         EnableCursor();
    //     } else if (IsKeyPressed(KEY_ESCAPE) and !IsCursorHidden()) {
    //         DisableCursor();
    //     }
    //
    //     if (IsKeyDown(KEY_LEFT_CONTROL)) {
    //         playerSpeed = 10.0f;
    //     } else {
    //         playerSpeed = 5.0f;
    //     }
    //
    //     Vector3 movementVector = {
    //         (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ? 1.0f : 0.0f) -
    //         (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ? 1.0f : 0.0f),
    //         (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ? 1.0f : 0.0f) -
    //         (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ? 1.0f : 0.0f),
    //         (IsKeyDown(KEY_SPACE) ? 1.0f : 0.0f) -
    //         (IsKeyDown(KEY_LEFT_SHIFT) ? 1.0f : 0.0f)
    //     };
    //
    //     if (Vector3Length(movementVector) > 0.0f)
    //         movementVector = Vector3Normalize(movementVector);
    //
    //     movementVector = Vector3Scale(movementVector, playerSpeed * GetFrameTime());
    //
    //     if (IsKeyDown(KEY_G)) {
    //         player.camera.position = Vector3{0.0f, 1.0f, 0.0f};
    //     }
    //
    //     if (IsCursorHidden()) {
    //         UpdateCameraPro(&player.camera,
    //             movementVector,
    //             Vector3{ GetMouseDelta().x * sensitivity, GetMouseDelta().y * sensitivity, 0.0f },
    //             0.0f
    //         );
    //     }
    //
    //     player.position = player.camera.position;
    //
    //     SetShaderValue(
    //     shader,
    //     locViewPos,
    //     &player.camera.position,
    //     SHADER_UNIFORM_VEC3
    //     );
    //
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);
    //     // BeginShaderMode(shader);
    //     BeginMode3D(player.camera);
    //
    //     DrawCube(Vector3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f, RED);
    //
    //     DrawGrid(100, 1.0f);
    //
    //     chunk.render(materials);
    //
    //     EndMode3D();
    //     // EndShaderMode();
    //
    //     if (!IsCursorHidden()) {
    //         DrawRectangle(0, 0, screenWidth, screenHeight, Color(128, 128, 128, 150));
    //     }
    //     DrawFPS(5, 0);
    //
    //     int positionAccuracy = 3;
    //     std::ostringstream xs;
    //     xs << std::fixed << std::setprecision(positionAccuracy) << player.position.x;
    //     std::string playerXString = xs.str();
    //
    //     std::ostringstream ys;
    //     ys << std::fixed << std::setprecision(positionAccuracy) << player.position.y;
    //     std::string playerYString = ys.str();
    //
    //     std::ostringstream zs;
    //     zs << std::fixed << std::setprecision(positionAccuracy) << player.position.z;
    //     std::string playerZString = zs.str();
    //
    //     std::string XPosText = "X: " + playerXString;
    //     std::string YPosText = "Y: " + playerYString;
    //     std::string ZPosText = "Z: " + playerZString;
    //
    //     DrawText(XPosText.c_str(), 5, 20, 20, BLUE);
    //     DrawText(YPosText.c_str(), 5, 45, 20, BLUE);
    //     DrawText(ZPosText.c_str(), 5, 70, 20, BLUE);
    //
    //     EndDrawing();
    // }
    // std::cout << "[SHUTDOWN] Starting shutdown..." << std::endl;
    //
    // std::cout << "[SHUTDOWN] Unloading materials" << std::endl;
    // materials.unloadMaterials();
    // std::cout << "[SHUTDOWN] Unloaded materials" << std::endl;
    //
    // UnloadShader(shader);
    // std::cout << "[SHUTDOWN] Unloaded shader" << std::endl;
    //
    // textureManager.unloadTextures();
    // std::cout << "[SHUTDOWN] Unloaded textures" << std::endl;
    //
    // // blockModel.materialCount = 0;
    // // blockModel.materials = nullptr;
    // // UnloadModel(blockModel);
    // // std::cout << "[SHUTDOWN] Unloaded block model" << std::endl;
    //
    // CloseWindow();
    //
    // std::cout << "[SHUTDOWN] Successfully shutdown everything!" << std::endl;

    return 0;
}
