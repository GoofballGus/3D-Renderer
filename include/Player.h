#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include <algorithm>
#include <string>
#include "Configs.h"


class Player {
public:
    Player();
    explicit Player(Vector3 pos);
    void update(float deltaTime, const World& world);

    Camera3D* getCamera();
    void renderHands();

    float verticalVelocity = 0.0f;
    Vector2 horizontalVelocity{};
    float MAX_HORIZONTAL_VELOCITY;
    float MIN_HORIZONTAL_VELOCITY;

    float GRAVITY;
    float JUMP_FORCE;
    float ACCELERATION;
    float FRICTION;
    float AIR_FRICTION;
    float SPRINT_SPEED;
    float NORMAL_SPEED;

    bool grounded = false;

    float sensitivity;

    Vector3 position{};

    float FOV;
    Camera3D camera{};
private:
    YAML::Node config;
};


#endif //PLAYER_H
