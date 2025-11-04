//
// Created by User on 02/11/2025.
//

#ifndef CONFIGS_H
#define CONFIGS_H
#pragma once
#include <yaml-cpp/yaml.h>


namespace Configs {
    extern YAML::Node PLAYER;
    extern YAML::Node GAME;

    void Load();
}

#endif //CONFIGS_H
