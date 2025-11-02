#include "../include/Block.h"

Block::Block(const unsigned int id, Material& mat, const std::string &name, Model mod)
    : id(id), name(name), material(&mat), model(mod) {
    model.materials[0] = *material;
}

Model Block::getModel() const {
    return model;
}
