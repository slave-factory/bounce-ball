#include "block.hpp"
#include <memory>
#include <cmath>

Block::Block(BlockType t, sf::Vector2f pos)
    : type(t), position(pos) {}

BlockType Block::getType() const {
    return type;
}

sf::Vector2f Block::getPosition() const {
    return position;
}

std::shared_ptr<sf::Shape> Block::getShape() const {
    if (type == BlockType::Solid || type == BlockType::OneTime) {
        auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(blockLen - blockOutline, blockLen - blockOutline));
        rect->setOrigin(blockLen / 2, blockLen / 2);
        rect->setPosition(position);
        rect->setOutlineThickness(blockOutline);
        rect->setOutlineColor(sf::Color::Black);
        rect->setFillColor(type == BlockType::Solid ? sf::Color(128, 128, 128) : sf::Color::Transparent);
        return rect;
    } else if (type == BlockType::Star) {
        auto star = std::make_shared<sf::ConvexShape>(10);
        float outerRadius = (blockLen - blockOutline) / 2.f;
        float innerRadius = outerRadius * 0.4f;

        for (int k = 0; k < 10; ++k) {
            float angle = k * 36 * 3.14159265f / 180.f - 3.14159265f / 2;
            float radius = (k % 2 == 0) ? outerRadius : innerRadius;
            float x = position.x + radius * cos(angle);
            float y = position.y + radius * sin(angle);
            star->setPoint(k, sf::Vector2f(x, y));
        }

        star->setFillColor(sf::Color::Yellow);
        star->setOutlineThickness(blockOutline);
        star->setOutlineColor(sf::Color::Black);
        return star;
    }

    return nullptr;
}

void Block::draw(sf::RenderWindow& window) const {
    auto shape = getShape();
    if (shape) {
        window.draw(*shape);
    }
}
