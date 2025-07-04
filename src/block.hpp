#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>  // for std::shared_ptr

// 🔧 BlockType 열거형 정의 추가
enum class BlockType {
    None,
    Solid,
    OneTime,
    Star,
    Jump
};

class Block {
private:
    BlockType type;
    sf::Vector2f position;

    float blockLen = 30.f;
    float blockOutline = 1.f;
    float winGap = 3.f;

    static sf::Texture windowTexture;
    static bool textureLoadedOne;

    static sf::Texture jumpTexture;
    static bool textureLoadedJump;

public:
    Block(BlockType t, sf::Vector2f pos);

    BlockType getType() const;
    sf::Vector2f getPosition() const;

    static bool loadTextureOnetime(const std::string& filename);
    static bool loadTextureJump(const std::string& filename);

    std::shared_ptr<sf::Shape> getShape() const;
    void draw(sf::RenderWindow& window) const;
};
