#include "../include/Player.h"


Player::Player() {}

Player::Player(const Vector3 pos) {
    position = pos;
    FOV = 60.0f;

    camera.position = position;
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = FOV;
    camera.projection = CAMERA_PERSPECTIVE;

    config = Configs::PLAYER;

    GRAVITY = config["gravity"].as<float>();
    JUMP_FORCE = config["jump_force"].as<float>();
    ACCELERATION = config["acceleration"].as<float>();
    FRICTION = config["friction"].as<float>();
    AIR_FRICTION = config["air_friction"].as<float>();

    sensitivity = config["sensitivity"].as<float>();

    MAX_HORIZONTAL_VELOCITY = config["max_horizontal_velocity"].as<float>();
    MIN_HORIZONTAL_VELOCITY = config["min_horizontal_velocity"].as<float>() * -1.0f;

    SPRINT_SPEED = config["sprint_speed"].as<float>();
    NORMAL_SPEED = config["normal_speed"].as<float>();
}

Camera3D* Player::getCamera() {
    return &camera;
}

void Player::renderHands() {
    // TODO: Implement hand rendering
}

void Player::update(float deltaTime, const World& world) {
    position = camera.position;

    // Toggle cursor
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (IsCursorHidden()) EnableCursor();
        else DisableCursor();
    }

    // Speed modifier
    float currentSpeed = IsKeyDown(KEY_LEFT_CONTROL) ? SPRINT_SPEED : NORMAL_SPEED;
    // TODO: Make sprinting work with the config file speeds

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
    horizontalVelocity.x = std::clamp(horizontalVelocity.x, MIN_HORIZONTAL_VELOCITY, MAX_HORIZONTAL_VELOCITY);
    horizontalVelocity.y = std::clamp(horizontalVelocity.y, MIN_HORIZONTAL_VELOCITY, MAX_HORIZONTAL_VELOCITY);

    // Apply friction only when grounded
    if (grounded) {
        horizontalVelocity.x *= FRICTION;
        horizontalVelocity.y *= FRICTION;
    }

    // --- VERTICAL MOVEMENT ---
    if (!grounded){
        horizontalVelocity.x *= AIR_FRICTION;
        horizontalVelocity.y *= AIR_FRICTION;

        verticalVelocity += GRAVITY * deltaTime;
    }

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
    if (camera.position.y <= 0.5f) { // floor at Y=1
        camera.position.y =  0.5f;
        verticalVelocity = 0.0f;
        grounded = true;
    } else {
        grounded = false;
    }

    // Update Player position
    position = camera.position;
}
