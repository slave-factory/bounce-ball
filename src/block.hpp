#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory> 

enum class BlockType {
    None,
    Solid,
    OneTime,
    Star
};

class Block {
private:
    BlockType type;
    sf::Vector2f position;

    static constexpr float blockLen = 30.f;
    static constexpr float blockOutline = 1.f;
    static constexpr float winGap = 3.f;

public:
    Block(BlockType t, sf::Vector2f pos);

    BlockType getType() const;
    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window) const;
    std::shared_ptr<sf::Shape> getShape() const;
};
