#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class button {
    public:
        button(sf::Vector2f position, sf::Vector2f size, const std::string text);

        void render(sf::RenderWindow& window) const;
        bool isClicked(sf::Vector2f mousePos, int& selectedStage) const;

        void setFont(const sf::Font& font);

    private:
        sf::RectangleShape shape;
        sf::Text label;
        int stageNumber;
};
