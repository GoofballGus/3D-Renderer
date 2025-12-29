#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <unordered_map>
#include <iostream>
#include <magic_enum/magic_enum.hpp>

enum class BlockType {
    BLOCK_AIR,
    BLOCK_STONE,
    BLOCK_EXAMPLE,
};

const std::unordered_map<std::string, BlockType> blockTypeMap = {
    {"air", BlockType::BLOCK_AIR},
    {"stone", BlockType::BLOCK_STONE},
    {"example", BlockType::BLOCK_EXAMPLE},
};

inline BlockType StringToBlockType(const std::string& name) {
    auto it = blockTypeMap.find(name);
    if (it != blockTypeMap.end()) {
        return it->second;
    }

    std::cerr << name << " is not a valid block type." << std::endl;
    return BlockType::BLOCK_AIR;
}

#endif //BLOCKTYPE_H
