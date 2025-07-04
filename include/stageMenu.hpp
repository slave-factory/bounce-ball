#pragma once

#include "button.hpp"
#include <iostream>
#include <vector>

class stageMenu {

    public: 
        stageMenu();
        std::vector<button> getButtonList();

    private:
        std::vector<button> buttonList;
        sf::Font font;
};