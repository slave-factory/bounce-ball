#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball {
private:
    sf::CircleShape ball;
    float setOriginX = 130.f;
    float setOriginY = 400.f;
    float radius;
    float moveSpeed;

    float colBuffer = 3.5f;

    float jumpDelta = 90.f;
    float jumpY = 100.f;
    float jumpH = 50.f;
    float jumpS = 0.5f;
    bool isOnGround = false;
    bool isJumping = false;

    float block_len = 30.f;

public:
    Ball(float r = 7.f, float speed = 0.5f);

    void handleInput();
    void Collide(const sf::RectangleShape& block);
    bool OneCollide(sf::RectangleShape& block);
    void applyGravity();
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
};
