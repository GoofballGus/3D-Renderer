#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "raylib.h"

class Game {
public:
    Game();
    void Run();
private:
    void Update();
    void Render();
};

#endif //GAME_H
