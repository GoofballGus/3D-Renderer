#include "../include/World.h"


World::World(int w, int h, int d)
    : width(w), height(h), depth(d), world(static_cast<size_t>(w) * h * d, nullptr) {}

void World::update(float dt) {}

void World::render(const AssetManager& assets) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < depth; ++z) {
                Block* block = at(x, y, z);
                if (block != nullptr) {
                    Vector3 position = {
                        static_cast<float>(x) * 0.6f,
                        static_cast<float>(y) * 0.6f,
                        static_cast<float>(z) * 0.6f
                    };
                    DrawModelEx(
                        block->getModel(),
                        position,
                        Vector3{0.0f, 1.0f, 0.0f},
                        0.0f,
                        Vector3{1.0f, 1.0f, 1.0f},
                        WHITE
                    );
                }
            }
        }
    }
}

Block*& World::at(int x, int y, int z) {
    assert(x >= 0 && x < width);
    assert(y >= 0 && y < height);
    assert(z >= 0 && z < depth);
    size_t idx = (static_cast<size_t>(x) * height + y) * depth + z;
    return world[idx];
}

void World::generateDefaultTerrain(AssetManager& assets) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < depth; ++z) {
                at(x,y,z) = assets.blocks.getBlock("broken");
            }
        }
    }
}
