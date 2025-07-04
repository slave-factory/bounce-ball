#include "../../include/button.hpp"
#include <string>

button::button(sf::Vector2f position, sf::Vector2f size, const std::string text) {

    stageNumber = std::stoi(text);

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(100, 100, 250)); 

    label.setString(text);
    label.setCharacterSize(40);
    label.setFillColor(sf::Color::White);
    label.setPosition(position.x + size.x / 2.0, position.y);
}

void button::render(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

bool button::isClicked(sf::Vector2f mousePos, int& selectedStage) const {
    selectedStage = stageNumber;
    return shape.getGlobalBounds().contains(mousePos);
}

void button::setFont(const sf::Font& font) {
    label.setFont(font);
}
