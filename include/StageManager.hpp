#ifndef STAGEMANAGER_HPP
#define STAGEMANAGER_HPP

#include <vector>
#include <memory>
#include "StageInfo.hpp"
#include "Block/Block.hpp"
#include "Block/Stone.hpp"
#include "Ball.hpp"
#include "Block/Star.hpp"
#include "Block/Jump.hpp"
#include "Block/Straight.hpp"
#include "Block/Needle.hpp"
#include "Block/Breakable.hpp"

class StageManager { 

    public : 
        StageManager(const std::string jsonPath);
        std::vector<std::unique_ptr<Block>> getMap(int stageNumber);
        sf::Vector2f getStartingPosition(int stageNumber);
        int getStarCount(int stageNumber);

    private : 
        std::vector<StageInfo> stageList;
        int selectedStage;
        void loadFromJson(std::string path);
};

#endif