#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include <vector>

const float block_len = 30.f;
const float block_outline = 1.f;
const int ROWS = 20;  
const int COLS = 20;  

int map[ROWS][COLS] = {
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},

    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,1,1, 1,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},

    {0,0,0,0,0,  0,0,0,0,0,  1,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,1,1,0,0,  0,0,0,1,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  1,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  1,1,1,1,1,  1,0,0,0,0, 0,0,0,0,0},

    {0,0,0,0,1,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0}
    
};

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Bounce Ball");
    Ball ball;

    std::vector<sf::RectangleShape> blocks;
    
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (map[i][j] == 1) {
                sf::RectangleShape block(sf::Vector2f(block_len - block_outline, block_len - block_outline));
                block.setFillColor(sf::Color::White);
                block.setOutlineThickness(block_outline);
                block.setOutlineColor(sf::Color::Black);
                block.setOrigin(block_len/2, block_len/2);
                block.setPosition(j * block_len + block_len/2, i * block_len + block_len/2);
                blocks.push_back(block);
            }
        }
    }

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.handleInput();
        ball.applyGravity();

        for (auto& block : blocks) {
            ball.Collide(block);
        }

        window.clear(sf::Color::White);
        ball.draw(window);

        for (const auto& block : blocks) {
            window.draw(block);
        }
        std::cout << "" << std::endl;
        window.display();
    }

    return 0;
}
