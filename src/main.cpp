#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include <vector>
#include <cmath>
const float block_len = 30.f;
const float block_outline = 1.f;

const float winGap = 3.f;

const int ROWS = 20;  
const int COLS = 20;  

int map[ROWS][COLS] = {
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,0,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},

    {0,0,1,0,0,  0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0},
    {0,0,1,0,0,  0,0,0,0,0,  0,0,0,0,0, 1,0,0,0,0},
    {0,0,1,0,0,  0,0,0,0,0,  0,0,0,0,0, 1,0,0,0,0},
    {0,0,1,0,0,  0,0,0,0,0,  0,0,0,0,0, 1,0,0,0,0},
    {0,0,1,1,1,  1,1,1,0,1,  0,0,0,0,1, 1,0,0,0,0},

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

    std::vector<sf::RectangleShape> blocks;
    std::vector<sf::RectangleShape> one_blocks;
    std::vector<sf::ConvexShape> stars;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (map[i][j] == 1) {
                sf::RectangleShape block(sf::Vector2f(block_len - block_outline, block_len - block_outline));
                block.setFillColor(sf::Color(128, 128, 128));
                block.setOutlineThickness(block_outline);
                block.setOutlineColor(sf::Color::Black);
                block.setOrigin(block_len/2, block_len/2);
                block.setPosition(j * block_len + block_len/2, i * block_len + block_len/2);
                blocks.push_back(block);
            }
            if (map[i][j] == 2) {
                sf::RectangleShape one_block(sf::Vector2f(block_len - block_outline, block_len - block_outline));
                one_block.setOutlineThickness(block_outline);
                one_block.setOutlineColor(sf::Color::Black);
                one_block.setOrigin(block_len/2, block_len/2);
                one_block.setPosition(j * block_len + block_len/2, i * block_len + block_len/2);
                one_blocks.push_back(one_block);
            }
            if (map[i][j] == 3) {
                sf::ConvexShape star;
                star.setPointCount(10);

                float centerX = j * block_len + block_len / 2;
                float centerY = i * block_len + block_len / 2;
                float outerRadius = (block_len - block_outline) / 2.f;
                float innerRadius = outerRadius * 0.4f;

                for (int k = 0; k < 10; ++k) {
                    float angle = k * 36 * 3.14159265f / 180.f - 3.14159265f / 2;
                    float radius = (k % 2 == 0) ? outerRadius : innerRadius;

                    float x = centerX + radius * cos(angle);
                    float y = centerY + radius * sin(angle);

                    star.setPoint(k, sf::Vector2f(x, y));
                }

                star.setFillColor(sf::Color::Yellow);
                star.setOutlineThickness(block_outline);
                star.setOutlineColor(sf::Color::Black);

                stars.push_back(star);
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

        for (auto it = one_blocks.begin(); it != one_blocks.end(); ) {
            if (ball.OneCollide(*it)) {
                it = one_blocks.erase(it); 
            } else {
                ++it;
            }
        }

        for (auto it = stars.begin(); it != stars.end(); ) {
            if (ball.StarCollide(*it)) {
                it = stars.erase(it); 
            } else {
                ++it;
            }
        }


        window.clear(sf::Color::White);
        ball.draw(window);


        for (const auto& star : stars) {
            window.draw(star);
        }

        for (const auto& block : blocks) {
            window.draw(block);
        }

        for (const auto& block : one_blocks) {
            sf::Vector2f oneWindow = block.getPosition();
            
            sf::RectangleShape Win1(sf::Vector2f(block_len/2 - winGap, block_len/2  - winGap)); 
            Win1.setPosition(oneWindow.x - block_len/2, oneWindow.y - block_len/2);       
            Win1.setOutlineThickness(block_outline);
            Win1.setOutlineColor(sf::Color::Black);             

            sf::RectangleShape Win2(sf::Vector2f(block_len/2  - winGap, block_len/2 - winGap)); 
            Win2.setPosition(oneWindow.x , oneWindow.y - block_len/2);        
            Win2.setOutlineThickness(block_outline);
            Win2.setOutlineColor(sf::Color::Black);                         

            sf::RectangleShape Win3(sf::Vector2f(block_len/2 - winGap, block_len/2 - winGap)); 
            Win3.setPosition(oneWindow.x - block_len/2, oneWindow.y);           
            Win3.setOutlineThickness(block_outline);
            Win3.setOutlineColor(sf::Color::Black);                      

            sf::RectangleShape Win4(sf::Vector2f(block_len/2 - winGap, block_len/2 - winGap)); 
            Win4.setOutlineThickness(block_outline);
            Win4.setOutlineColor(sf::Color::Black);             
            Win4.setPosition(oneWindow.x, oneWindow.y);                    


            window.draw(Win1);
            window.draw(Win2);
            window.draw(Win3);
            window.draw(Win4);
        }
        std::cout << "" << std::endl;
        window.display();
    }

    return 0;
}
