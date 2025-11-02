#include <string>
#include <vector>
#include "../include/Chunk.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "../include/main.h"
#include "raymath.h"
#include "../include/Materials.h"


bool Chunk::is_in_bounds(const int x, const int y, const int z) {
    return
    x >= 0 && x < CHUNK_WIDTH &&
    y >= 0 && y < CHUNK_HEIGHT &&
    z >= 0 && z < CHUNK_DEPTH;
}

Chunk::Chunk(Mesh* mesh, Model* model, const Vector3 pos, const Textures& textures) {
    blocks.resize(CHUNK_WIDTH);
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        blocks[x].resize(CHUNK_HEIGHT);
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            blocks[x][y].resize(CHUNK_DEPTH);
        }
    }

    TraceLog(LOG_INFO, "[DEBUG] Resized blocks vector");
    blockMesh = mesh;
    TraceLog(LOG_INFO, "[DEBUG] Set blockMesh");
    blockModel = model;
    TraceLog(LOG_INFO, "[DEBUG] Set blockModel");
    position = Vector3(pos.x + CHUNK_WIDTH / 2.0f, pos.y + CHUNK_HEIGHT / 2.0f, pos.z + CHUNK_DEPTH / 2.0f);
    TraceLog(LOG_INFO, "[DEBUG] Changed the chunk position");

    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
        for (int z = 0; z < CHUNK_DEPTH; ++z) {
            for (int x = 0; x < CHUNK_WIDTH; ++x) {
                Vector3 blockPos = { static_cast<float>(x) + pos.x, static_cast<float>(y) + pos.y, static_cast<float>(z) + pos.z };
                // TraceLog(LOG_INFO, "[DEBUG] Made blockPos");
                __int16 id = (y < CHUNK_HEIGHT / 2) ? textures.getBlockIdFromName("stone") : textures.getBlockIdFromName("dirt");
                // TraceLog(LOG_INFO, "[DEBUG] Set block id");
                // blocks[x][y][z] = Block(id, blockPos);  // TODO(): Remove comment after testing
                blocks[x][y][z]  = Block(1, blockPos);  // TODO(): Remove after testing
                // TraceLog(LOG_INFO, "[DEBUG] Set block at (%d, %d, %d) to id %d", x, y, z, id);
            }
        }
    }

    TraceLog(LOG_INFO, "[DEBUG] Finished init");
}

Block& Chunk::getBlock(int x, int y, int z) {
    if (!is_in_bounds(x, y, z)) {
        TraceLog(LOG_ERROR, "Attempted to get a block out of bounds at (%d, %d, %d)", x, y, z);
        return blocks[0][0][0];
    }
    return blocks[x][y][z];
}

void Chunk::setBlock(const int x, const int y, const int z, const __int16 id) {
    if (is_in_bounds(x, y, z)) {
        TraceLog(LOG_INFO, "Block at (%d, %d, %d) is set with id: %d", x, y, z, id);
        blocks[x][y][z].id = id;
    } else {
        TraceLog(LOG_ERROR, "Attempted to set a block out of bounds at (%d, %d, %d)", x, y, z);
    }
}

void Chunk::render(const Materials& materials) const {
    std::unordered_map<unsigned __int16, std::vector<Matrix>> blockMatrices;

    for (const auto& block1 : blocks) {
        for (const auto& block2 : block1) {
            for (const auto& block : block2) {
                if (block.id == 1) continue; // skip air
                blockMatrices[block.id].push_back(MatrixTranslate(block.position.x, block.position.y, block.position.z));
            }
        }
    }

    std::cout << "blockMatrices" << std::endl;
    for (const auto&[id, matrix] : blockMatrices) {
        std::cout << "  ID: " << id << " Count: " << matrix.size() << std::endl;
    }

    for (auto &[blockID, matrices] : blockMatrices) {
        Material mat = materials.getMaterialById(blockID);
        DrawMeshInstanced(*blockMesh, mat, matrices.data(), matrices.size());
    }

    DrawCubeWires(position, CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_DEPTH, GREEN);
}
