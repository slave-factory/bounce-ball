#include <SFML/Graphics.hpp>
#include "ball.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce Ball");
    Ball ball;

    sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
    block.setOrigin(15.f, 15.f);
    block.setPosition(400.f, 450.f);
    block.setFillColor(sf::Color::White);
    block.setOutlineThickness(1.f);
    block.setOutlineColor(sf::Color::Black);

    sf::RectangleShape block1(sf::Vector2f(30.f, 30.f));
    block1.setOrigin(15.f, 15.f);
    block1.setPosition(200.f, 450.f);
    block1.setFillColor(sf::Color::White);
    block1.setOutlineThickness(1.f);
    block1.setOutlineColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.handleInput();
        ball.applyGravity();
        ball.Collide(block);
        ball.Collide(block1);

        window.clear(sf::Color::White);
        ball.draw(window);
        window.draw(block);
        window.draw(block1);
        window.display();
    }

    return 0;
}
