#include "../../include/stageMenu.hpp"
#include <string>

stageMenu::stageMenu()  {

    font.loadFromFile("resource/fonts/AGENCYB.TTF");  // 한 번만 로드

    for (int i = 1; i < 4; i++) {
        button b(sf::Vector2f(100.f * i * 3, 100.f), sf::Vector2f(100.f, 100.f), std::to_string(i));
        b.setFont(font); // 멤버 font 사용
        buttonList.push_back(b);
    }

}


std::vector<button> stageMenu::getButtonList() {
    return this->buttonList;
}