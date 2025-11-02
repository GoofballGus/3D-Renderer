#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include "World.h"
#include <algorithm>
#include <string>


class Player {
public:
    explicit Player(Vector3 pos);
    void update(float deltaTime, const World& world);

    Camera3D* getCamera();
    void renderHands();
    void showTest();

    float verticalVelocity = 0.0f;
    Vector2 horizontalVelocity{}; // persistent horizontal velocity

    const float GRAVITY = -3.8f;
    const float JUMP_FORCE = 10.0f;
    const float ACCELERATION = 10.0f; // adjust to taste
    const float FRICTION = 0.85f;     // adjust for how slippery ground is

    bool grounded = false;

    float sensitivity = 0.2f;

    Vector3 position{};

    float FOV;
    Camera3D camera{};
};



#endif //PLAYER_H
