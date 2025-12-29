#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include "AssetManager.h"
#include <map>
#include "Block.h"


class BlockManager {
public:
    explicit BlockManager(AssetManager* asset_manager);
    Block* GetBlock(BlockType blockType);
    void UnloadBlocks();
private:
    AssetManager* assetManager;
    std::unordered_map<BlockType, Block*> blocks;
};


#endif //BLOCKMANAGER_H
