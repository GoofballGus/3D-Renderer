#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <filesystem>
#include <map>
#include <array>
#include "raylib.h"
#include "BlockType.h"
#include "ItemType.h"
#include "BlockModel.h"


class AssetManager {
public:
    void LoadAssets();
    void UnloadAssets();

    Texture2D* GetTexture(BlockType blockType);
    Texture2D* GetTexture(ItemType itemType);

    Model* GetModel(BlockModel blockType);
    Model* GetModel(ItemType itemType);

    Material* GetMaterial(BlockType blockType);

private:
    void LoadTextures();
    void LoadModels();
    void LoadMaterials();

    void UnloadTextures();
    void UnloadModels();
    void UnloadMaterials();

    std::pmr::map<BlockType, Texture2D> blockTextures;
    std::pmr::map<ItemType, Texture2D> itemTextures;
    std::pmr::map<BlockType, Material> blockMaterials;

    std::pmr::map<BlockModel, Model> blockModels;
    std::pmr::map<ItemType, Model> itemModels;

    Texture2D errorTexture;
};


#endif //ASSETMANAGER_H
