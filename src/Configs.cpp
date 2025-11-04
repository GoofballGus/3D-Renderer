#include "../include/Configs.h"


namespace Configs {
    YAML::Node PLAYER;

    void Load() {
        PLAYER = YAML::LoadFile("config/player.yaml");
    }
}
