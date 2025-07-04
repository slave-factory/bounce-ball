#include <iostream>
#include <fstream>

#include "StageManager.hpp"
#include "json.hpp"

using json = nlohmann::json;

StageManager::StageManager(const std::string jsonPath) {
    loadFromJson(jsonPath);
}

void StageManager::loadFromJson(std::string path) {

    std::ifstream file(path);
    json j;
    file >> j;

    for (const auto& stageJson : j["stages"]) {
        StageInfo stageInfo;
        stageInfo.stageNumber = stageJson["stage"];
        stageInfo.startX = stageJson["startX"];
        stageInfo.startY = stageJson["startY"];
        stageInfo.starCount = 0;

        for (const auto& block : stageJson["blocks"]) {
            if (block["type"].get<std::string>().compare("Stone") == 0) {
                stageInfo.blockList.push_back(std::make_unique<Stone>(block["x"].get<float>(), block["y"].get<float>(), 
                block["width"].get<float>(), block["height"].get<float>(), block["blockSize"].get<float>()));
            }
            else if (block["type"].get<std::string>().compare("Jump") == 0){
                stageInfo.blockList.push_back(std::make_unique<Jump>(block["x"].get<float>(), block["y"].get<float>()));
            }
            else if (block["type"].get<std::string>().compare("Star") == 0){
                stageInfo.blockList.push_back(std::make_unique<Star>(block["x"].get<float>(), block["y"].get<float>()));
                stageInfo.starCount++;
            }
            else if (block["type"].get<std::string>().compare("Needle") == 0){
                stageInfo.blockList.push_back(std::make_unique<Needle>(block["x"].get<float>(), block["y"].get<float>(), 
                block["width"].get<float>(), block["height"].get<float>()));
            }
            else if (block["type"].get<std::string>().compare("Straight") == 0){
                stageInfo.blockList.push_back(std::make_unique<Straight>(block["x"].get<float>(), block["y"].get<float>(), block["isRight"].get<bool>()));
            }
            else if (block["type"].get<std::string>().compare("Breakable") == 0){
                stageInfo.blockList.push_back(std::make_unique<Breakalbe>(block["x"].get<float>(), block["y"].get<float>()));
            }
        }
        // unique를 넘기는거라 move로 넘겨야 함
        stageList.push_back(std::move(stageInfo));
    }
}

std::vector<std::unique_ptr<Block>> StageManager::getMap(int stageNumber) {
    return std::move(stageList[stageNumber - 1].blockList);
}

sf::Vector2f StageManager::getStartingPosition(int stageNumber) {
    return sf::Vector2f(stageList[stageNumber - 1].startX, stageList[stageNumber - 1].startY);
}

int StageManager::getStarCount(int stageNumber) {
    return stageList[stageNumber - 1].starCount;
}