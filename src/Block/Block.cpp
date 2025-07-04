#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../include/Block/Block.hpp"

Block::Block(float x, float y, float width, float height, float blockSize, std::string image) 
    : position(x * 64.f,y * 64.f), size(width * 64.f, height * 64.f), blockSize(blockSize){

    // 최소 단위 블록 객체를 texture에 불러오기
    if (!texture.loadFromFile(image)) {
        std::cout << "블록 이미지 불러오기 실패";
    }

    isDraw = true;
    createRenderTexture();
    moveBlock(position.x, position.y);
}


void Block :: createRenderTexture() {

    // renderTexture 공간 만들기
    renderTexture.create(size.x, size.y);

    for (int y = 0; y < size.y / blockSize; y++) {
        for (int x = 0; x < size.x / blockSize; x++) {
            sf::Sprite temp(texture);
            temp.setPosition(x * blockSize, y * blockSize);
            renderTexture.draw(temp);
        }
    }

    renderTexture.display();
    sprite.setTexture(renderTexture.getTexture());
}

// 블록 위치 옮기기 and 경계 수정
void Block::moveBlock(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(sf::Vector2f(x,y));
    boundary = sprite.getGlobalBounds();
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);   
}