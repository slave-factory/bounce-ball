#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Block/Block.hpp"

struct StageInfo {
    int stageNumber;
    float startX;
    float startY;
    int starCount;
    std::vector<std::unique_ptr<Block>> blockList;
    bool unlocked;
};