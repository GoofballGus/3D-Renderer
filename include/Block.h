#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

struct Block {
    Texture2D* texture; // optional, for metadata
    Model* model;       // owns Model struct + materials[]

    ~Block() {
        if (model) {
            if (model->materials) {
                MemFree(model->materials); // free what you allocated
            }
            delete model; // delete only the struct
        }
    }
};

#endif // BLOCK_H
