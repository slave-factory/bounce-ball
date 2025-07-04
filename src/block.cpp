#include "block.hpp"
#include <memory>

sf::Texture Block::windowTexture;
bool Block::textureLoadedOne = false;

sf::Texture Block::jumpTexture;
bool Block::textureLoadedJump = false;

Block::Block(BlockType t, sf::Vector2f pos)
    : type(t), position(pos) {}

BlockType Block::getType() const {
    return type;
}

sf::Vector2f Block::getPosition() const {
    return position;
}

bool Block::loadTextureOnetime(const std::string& filename) {
    if (!windowTexture.loadFromFile(filename)) {
        return false;
    }
    textureLoadedOne = true;
    return true;
}

bool Block::loadTextureJump(const std::string& filename) {
    if (!jumpTexture.loadFromFile(filename)) {
        return false;
    }
    textureLoadedJump = true;
    return true;
}

std::shared_ptr<sf::Shape> Block::getShape() const {
    if (type == BlockType::None) return nullptr;

    if (type == BlockType::Solid || type == BlockType::OneTime ||  type == BlockType::Jump) {
        auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(blockLen - blockOutline, blockLen - blockOutline));
        rect->setOrigin(blockLen / 2, blockLen / 2);
        rect->setPosition(position);
        rect->setOutlineThickness(blockOutline);
        rect->setOutlineColor(sf::Color::Black);

        if (type == BlockType::Solid) {
            rect->setFillColor(sf::Color(128, 128, 128)); // gray
        } else if (type == BlockType::OneTime) {
            rect->setFillColor(sf::Color::Transparent); 
        } else if (type == BlockType::Jump) {
            rect->setFillColor(sf::Color::Blue);
        }

        return rect;
    }

    if (type == BlockType::Star) {
        auto star = std::make_shared<sf::ConvexShape>(10);
        float outerRadius = (blockLen - blockOutline) / 2.f;
        float innerRadius = outerRadius * 0.4f;
        float centerX = position.x;
        float centerY = position.y;

        for (int k = 0; k < 10; ++k) {
            float angle = k * 36 * 3.14159265f / 180.f - 3.14159265f / 2;
            float radius = (k % 2 == 0) ? outerRadius : innerRadius;

            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);

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
    if (type == BlockType::OneTime && textureLoadedOne) {
        sf::Sprite sprite;
        sprite.setTexture(windowTexture);
        sprite.setScale(blockLen / windowTexture.getSize().x, blockLen / windowTexture.getSize().y);
        sprite.setPosition(position.x - blockLen / 2, position.y - blockLen / 2);
        window.draw(sprite);
    } else if (type == BlockType::Jump && textureLoadedJump) {
        sf::Sprite sprite;
        sprite.setTexture(jumpTexture);
        sprite.setScale(blockLen / jumpTexture.getSize().x, blockLen / jumpTexture.getSize().y);
        sprite.setPosition(position.x - blockLen / 2, position.y - blockLen / 2);
        window.draw(sprite);
    } else {
        auto shape = getShape();
        if (shape) {
            window.draw(*shape);
        }
    }
}
