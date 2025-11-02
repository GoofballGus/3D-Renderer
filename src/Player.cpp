#include "../include/Player.h"


Player::Player(Vector3 pos) {
    position = pos;
    FOV = 60.0f;

    Camera playerCamera = {};
    playerCamera.position = position;
    playerCamera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    playerCamera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    playerCamera.fovy = FOV;
    playerCamera.projection = CAMERA_PERSPECTIVE;

    camera = playerCamera;
}

Camera3D* Player::getCamera() {
    return &camera;
}

void Player::renderHands() {
    // DrawText("PLAYER!!!", 100, 100, 10, RED);
}

void Player::update(float deltaTime, const World& world) {
    position = camera.position;

    // Toggle cursor
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (IsCursorHidden()) EnableCursor();
        else DisableCursor();
    }

    // Speed modifier
    float currentSpeed = IsKeyDown(KEY_LEFT_CONTROL) ? 10.0f : 5.0f;

    // --- INPUT ---
    Vector2 inputDir = {
        static_cast<float>(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)), // forward/back
        static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) // right/left
    };

    if (Vector2Length(inputDir) > 0) {
        inputDir = Vector2Normalize(inputDir);
    }

    // --- HORIZONTAL VELOCITY ---
    // Apply acceleration
    horizontalVelocity.x += inputDir.x * ACCELERATION * deltaTime;
    horizontalVelocity.y += inputDir.y * ACCELERATION * deltaTime;

    // Clamp velocity to [-1, 1] (or whatever max you want)
    horizontalVelocity.x = std::clamp(horizontalVelocity.x, -0.8f, 1.2f);
    horizontalVelocity.y = std::clamp(horizontalVelocity.y, -0.8f, 1.2f);

    // Apply friction only when grounded
    if (grounded) {
        horizontalVelocity.x *= FRICTION;
        horizontalVelocity.y *= FRICTION;
    }

    // --- VERTICAL MOVEMENT ---
    if (!grounded)
        verticalVelocity += GRAVITY * deltaTime;

    // Jump
    if (IsKeyPressed(KEY_SPACE) && grounded) {
        verticalVelocity = JUMP_FORCE;
        grounded = false;
    }

    float verticalMove = verticalVelocity * deltaTime;

    // --- COMBINE MOVEMENT ---
    Vector3 movementVector = {
        horizontalVelocity.x * currentSpeed * deltaTime,
        horizontalVelocity.y * currentSpeed * deltaTime,
        verticalMove };

    // --- UPDATE CAMERA ---
    if (IsCursorHidden()) {
        UpdateCameraPro(&camera,
                        movementVector,
                        Vector3{ GetMouseDelta().x * sensitivity,
                            GetMouseDelta().y * sensitivity,
                            0.0f },
                        0.0f);
    }

    // --- GROUND COLLISION ---
    if (camera.position.y <= -3.0f) { // floor at Y=1
        camera.position.y = -3.0f;
        verticalVelocity = 0.0f;
        grounded = true;
    } else {
        grounded = false;
    }

    // Update Player position
    position = camera.position;
}
