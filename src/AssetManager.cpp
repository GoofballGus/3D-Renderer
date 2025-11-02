#include "../include/AssetManager.h"


// AssetManager methods
void AssetManager::Setup() {
    const FilePathList texturesPathList = LoadDirectoryFiles("assets/textures/");
    for (int i = 0; i < texturesPathList.count; ++i) {
        std::string fullPath = texturesPathList.paths[i];
        std::string textureName = fullPath.substr(
            fullPath.find_last_of('/') + 1,
            fullPath.find_last_of('.') - fullPath.find_last_of('/') - 1
        );
        textureName.erase(0, 1);
        std::cout << "Loading texture: " << textureName << std::endl;
        textures.Load(textureName);
        materials.Create(textureName, *textures.Get(textureName));

        const Model blockModel = LoadModel("assets/models/cube/cube.obj");
        blocks.init(blockModel);

        blocks.Create(i, *materials.Get(textureName), textureName);
    }
    UnloadDirectoryFiles(texturesPathList);
}


// TextureManager methods
Texture2D* TextureManager::Get(const std::string &name) {
    auto iterator = textures.find(name);
    if (iterator == textures.end()) return nullptr;
    return &iterator->second;
}

void TextureManager::Load(const std::string &name) {
    Texture2D texture = LoadTexture((baseTexturePath + name + ".png").c_str());
    textures[name] = texture;
}

void TextureManager::UnloadAll() {
    TraceLog(LOG_INFO, "TextureManager UnloadAll starting");
    for (auto &pair : textures) {
        UnloadTexture(pair.second);
    }

    textures.clear();
    TraceLog(LOG_INFO, "TextureManager UnloadAll starting");
}


// MaterialManager methods
Material *MaterialManager::Get(const std::string &name) {
    auto iterator = materials.find(name);
    if (iterator == materials.end()) return nullptr;
    return &iterator->second;
}

// Make sure &diffuse is from TextureManager
void MaterialManager::Create(const std::string &name, const Texture2D &diffuse) {
    Material newMaterial = LoadMaterialDefault();
    newMaterial.maps[MATERIAL_MAP_ALBEDO].texture = diffuse;
    materials[name] = newMaterial;
}

void MaterialManager::UnloadAll() {
    TraceLog(LOG_INFO, "MaterialManager UnloadAll starting");
    for (auto &pair : materials) {
        UnloadMaterial(pair.second);
    }

    materials.clear();
    TraceLog(LOG_INFO, "MaterialManager UnloadAll ended");
}


// BlockManager methods
void BlockManager::init(const Model &blockModel) {
    model = blockModel;
}

void BlockManager::Create(const unsigned int id, Material& mat, const std::string& name) {
    blocks.emplace(name, Block(id, mat, name, model));
}

Block *BlockManager::getBlock(const std::string &name) {
    return &blocks.at(name);
}
