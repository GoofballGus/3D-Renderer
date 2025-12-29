#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <unordered_map>
#include <iostream>

enum ItemType {
    ITEM_AIR,
    ITEM_STONE,
    ITEM_EXAMPLE
};

const std::unordered_map<std::string, ItemType> itemTypeMap = {
    {"air", ITEM_AIR},
    {"stone", ITEM_STONE},
    {"example", ITEM_EXAMPLE},
};

inline ItemType StringToItemType(const std::string& name) {
    auto it = itemTypeMap.find(name);
    if (it != itemTypeMap.end()) {
        return it->second;
    }

    std::cerr << name << " is not a valid item type." << std::endl;
    return ITEM_AIR;
}

#endif //ITEMTYPE_H
