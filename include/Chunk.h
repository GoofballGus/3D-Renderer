#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "Materials.h"
#include "Textures.h"

struct Block;

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 256;
constexpr int CHUNK_DEPTH = 16;

class Chunk {
public:
    std::vector<std::vector<std::vector<Block>>> blocks;
    Vector3 position{};

    void setBlock(int x, int y, int z, __int16 id);
    Block& getBlock(int x, int y, int z);
    void render(const Materials& materials) const;

    Chunk(Mesh* blockMesh, Model* model, Vector3 pos, const Textures& textures);

private:
    [[nodiscard]] static bool is_in_bounds(int x, int y, int z);
    Mesh* blockMesh;
    Model* blockModel{};
};

#endif //CHUNK_H
