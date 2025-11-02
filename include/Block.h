#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <utility>
#include "raylib.h"

class Block {
public:
    Block(unsigned int id, Material& mat, const std::string &name, Model mod);

    [[nodiscard]] Model getModel() const;
private:
    unsigned int id;
    std::string name;
    Material* material;
    Model model;
};


#endif //BLOCK_H
