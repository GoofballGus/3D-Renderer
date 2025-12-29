#include "AssetManager.h"
#include <ranges>
#include "BlockModel.h"


void AssetManager::LoadAssets() {
    LoadTextures();
    LoadModels();
    this->LoadMaterials();
}

void AssetManager::UnloadAssets() {
    UnloadMaterials();
    UnloadModels();
    UnloadTextures();
}

void AssetManager::LoadTextures() {
    const std::string baseTexturePath = ASSETS_PATH "textures/";

    // Block textures
    const std::filesystem::path blockTexturePath = baseTexturePath + "blocks/";
    errorTexture = LoadTexture((blockTexturePath.string() + "error.png").c_str());
    blockTextures.insert({
        BlockType::BLOCK_EXAMPLE,
        LoadTexture((blockTexturePath.string() + "example.png").c_str()),
    });
}

void AssetManager::LoadModels() {
    const std::string baseModelPath = ASSETS_PATH "models/";

    // Block models
    const std::filesystem::path blockModelPath = baseModelPath + "blocks/";
    blockModels.insert({
        MODEL_CUBE,
        LoadModel((blockModelPath.string() + "cube.obj").c_str()),
    });
}

void AssetManager::LoadMaterials() {
    for (BlockType blockType : magic_enum::enum_values<BlockType>()) {
        Material material = LoadMaterialDefault();

        // Use error texture if block texture doesn't exist
        if (blockTextures.find(blockType) != blockTextures.end()) {
            material.maps[MATERIAL_MAP_ALBEDO].texture = blockTextures[blockType];
            std::cout << "Loaded material: " << magic_enum::enum_name(blockType) << " albedo map" << std::endl;
        } else {
            material.maps[MATERIAL_MAP_ALBEDO].texture = errorTexture;
            std::cerr << "Warning: No texture found for block type " << magic_enum::enum_name(blockType) << ", using error texture" << std::endl;
        }

        blockMaterials.insert({blockType, material});
    }
}

Texture2D* AssetManager::GetTexture(BlockType type) {
    auto it = blockTextures.find(type);
    if (it != blockTextures.end()) {
        return &it->second;
    }

    std::cerr << "Warning: Failed to find texture type " << magic_enum::enum_name(type) << std::endl;

    return &errorTexture; // NEVER nullptr
}

Texture2D* AssetManager::GetTexture(const ItemType itemType) {
    return &itemTextures[itemType];
}

Model* AssetManager::GetModel(const BlockModel blockType) {
    return &blockModels[blockType];
}

Model* AssetManager::GetModel(const ItemType itemType) {
    return &itemModels[itemType];
}

Material* AssetManager::GetMaterial(const BlockType blockType) {
    return &blockMaterials[blockType];
}

void AssetManager::UnloadTextures() {
    // Block textures
    for (auto &val: blockTextures | std::views::values) {
        UnloadTexture(val);
    }
    blockTextures.clear();

    // Item textures
    for (auto &val: itemTextures | std::views::values) {
        UnloadTexture(val);
    }
    itemTextures.clear();

    UnloadTexture(errorTexture);
}

void AssetManager::UnloadModels() {
    // Block models
    for (auto &val: blockModels | std::views::values) {
        UnloadModel(val);
    }
    blockModels.clear();

    // Item models
    for (auto &val: itemModels | std::views::values) {
        UnloadModel(val);
    }
    itemModels.clear();
}

void AssetManager::UnloadMaterials() {
    for (auto &val: blockMaterials | std::views::values) {
        UnloadMaterial(val);
    }
    blockMaterials.clear();
}
