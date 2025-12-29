#include "BlockManager.h"

BlockManager::BlockManager(AssetManager* asset_manager) {
    assetManager = asset_manager;

    Model* sourceModel = assetManager->GetModel(MODEL_CUBE);

    for (BlockType blockType : magic_enum::enum_values<BlockType>()) {
        Model* blockModel = new Model(*sourceModel); // copy struct

        // Allocate unique material array
        blockModel->materials = (Material*)MemAlloc(
            sizeof(Material) * blockModel->materialCount
        );

        blockModel->materials[0] =
            *assetManager->GetMaterial(blockType);

        blockModel->materials[0]
            .maps[MATERIAL_MAP_ALBEDO].texture =
                *assetManager->GetTexture(blockType);

        blocks[blockType] = new Block{
            assetManager->GetTexture(blockType),
            blockModel
        };
    }
}

Block* BlockManager::GetBlock(BlockType blockType) {
    return blocks[blockType];
}

void BlockManager::UnloadBlocks() {
    for (auto& [type, block] : blocks) {
        delete block;
    }
    blocks.clear();
}
