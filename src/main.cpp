#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> 
#include "ball.hpp"
#include "block.hpp"

const int ROWS = 20;
const int COLS = 20;

int map[ROWS][COLS] = {
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,1,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,1,0,0,  0,0,0,3,3,  3,3,0,0,0, 1,0,0,0,0},
    {0,0,1,0,0,  0,0,3,2,3,  0,0,0,0,0, 1,0,0,0,0},
    {0,0,1,0,0,  0,0,2,2,2,  0,0,0,0,0, 1,0,0,0,0},
    {0,0,1,1,1,  1,4,1,0,1,  0,0,0,0,1, 1,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  1,2,2,1,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  1,2,2,1,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  1,0,0,0,1, 1,1,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  1,0,0,0,3, 0,0,1,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,3,0, 3,0,1,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,1,1,1, 1,1,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Bounce Ball");
    Ball ball;

    if (!Block::loadTextureOnetime("Window.png")) {
    std::cerr << "이미지 불러오기 실패" << std::endl;
    return -1;
    }

    if (!Block::loadTextureJump("Jump.png")) {
    std::cerr << "이미지 불러오기 실패" << std::endl;
    return -1;
    }


    std::vector<Block> blocks;

    // 블록 초기화
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            BlockType type = BlockType::None;
            if (map[i][j] == 1) type = BlockType::Solid;
            else if (map[i][j] == 2) type = BlockType::OneTime;
            else if (map[i][j] == 3) type = BlockType::Star;
            else if (map[i][j] == 4) type = BlockType::Jump;
            if (type != BlockType::None) {
                sf::Vector2f pos(j * 30.f + 15.f, i * 30.f + 15.f);
                blocks.emplace_back(type, pos);
            }
        }
    }

    // 메인 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.handleInput();
        ball.applyGravity();

        // 충돌 처리
        for (auto it = blocks.begin(); it != blocks.end(); ) {
            std::shared_ptr<sf::Shape> shape = it->getShape();

            if (it->getType() == BlockType::Solid) {
                if (auto rect = dynamic_cast<sf::RectangleShape*>(shape.get())) {
                    ball.collide(*rect);
                }
                ++it;
            } else if (it->getType() == BlockType::OneTime) {
                if (auto rect = dynamic_cast<sf::RectangleShape*>(shape.get())) {
                    if (ball.oneCollide(*rect)) {
                        it = blocks.erase(it);
                        continue;
                    }
                }
                ++it;
            } else if (it->getType() == BlockType::Star) {
                if (auto star = dynamic_cast<sf::ConvexShape*>(shape.get())) {
                    if (ball.starCollide(*star)) {
                        it = blocks.erase(it);
                        continue;
                    }
                }
                ++it;
            } else if(it->getType() == BlockType::Jump) {
                if (auto rect = dynamic_cast<sf::RectangleShape*>(shape.get())) {
                    ball.jumpCollide(*rect);
                }
                ++it;
            } else {
                ++it;
            }
        }

        // 렌더링
        window.clear(sf::Color::White);
        ball.draw(window);
        for (const auto& block : blocks) {
            block.draw(window);
        }
        window.display();
    }

    return 0;
}
