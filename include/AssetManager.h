#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H


#include "raylib.h"
#include "string"
#include "unordered_map"
#include "Block.h"
#include <iostream>
#include <bits/ostream.tcc>
#include "../include/Block.h"


class TextureManager {
public:
    Texture2D* Get(const std::string& name);

    void Load(const std::string& name);

    void UnloadAll();
private:
    std::unordered_map<std::string, Texture2D> textures;
    std::string baseTexturePath = "assets/textures/";
};

class MaterialManager {
public:
    Material* Get(const std::string& name);

    void Create(const std::string& name, const Texture2D& diffuse);

    void UnloadAll();
private:
    std::unordered_map<std::string, Material> materials;
};

class BlockManager {
public:
    void init(const Model &blockModel);

    Block* getBlock(const std::string& name);
    void Create(unsigned int id, Material& mat, const std::string& name);

    const Model *getModel() const { return &model; }
private:
    Model model = {};
    std::unordered_map<std::string, Block> blocks;
};

class AssetManager {
public:
    TextureManager textures;
    MaterialManager materials;
    BlockManager blocks;

    void Shutdown() {
        materials.UnloadAll();  // Has pointers to textures
        textures.UnloadAll();
    }

    void Setup();
};



#endif //ASSETMANAGER_H
