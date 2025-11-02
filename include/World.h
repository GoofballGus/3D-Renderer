#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <cassert>
#include "../include/AssetManager.h"
#include "../include/Block.h"

class AssetManager;
class Block;

class World {
public:
    explicit World(int w = 100, int h = 100, int d = 100);
    void update(float dt);
    void render(const AssetManager& assets);
    void generateDefaultTerrain(AssetManager& assets);

    // access helper
    Block*& at(int x, int y, int z);

private:
    int width, height, depth;
    std::vector<Block*> world; // heap-backed flattened 3D array
};


#endif //WORLD_H
