#ifndef BLOCKMODEL_H
#define BLOCKMODEL_H

#include <iostream>
#include <unordered_map>

enum BlockModel {
    MODEL_CUBE
};

const std::unordered_map<std::string, BlockModel> blockModelMap = {
    {"cube", MODEL_CUBE},
};

inline BlockModel StringToBlockModel(const std::string& name) {
    auto it = blockModelMap.find(name);
    if (it != blockModelMap.end()) {
        return it->second;
    }

    std::cerr << name << " is not a valid block model." << std::endl;
    return MODEL_CUBE;
}

#endif //BLOCKMODEL_H
