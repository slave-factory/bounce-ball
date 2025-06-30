#include "ball.hpp"

Ball::Ball(float r, float speed)
    : radius(r), moveSpeed(speed), isOnGround(false) {
    ball.setRadius(radius);
    ball.setOrigin(radius,radius);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOutlineThickness(1.f);
    ball.setOutlineColor(sf::Color::Black);
    ball.setPosition(100.f, 400.f);  // 초기 위치
}

void Ball::handleInput() {
    sf::Vector2f pos = ball.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        ball.setPosition(pos.x - moveSpeed, pos.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        ball.setPosition(pos.x + moveSpeed, pos.y);
    }
}


void Ball::Collide(const sf::RectangleShape& block) {
    sf::Vector2f pos = ball.getPosition();
    sf::Vector2f block_pos = block.getPosition();
    
    // 상
    if (    
            pos.y + radius >= block_pos.y - block_len/2 - colBuffer
        &&  pos.y + radius <= block_pos.y - block_len/2 + colBuffer
        &&  pos.x <= block_pos.x + block_len/2 + colBuffer//왼쪽
        &&  pos.x >= block_pos.x - block_len/2 - colBuffer//오른쪽
        ) {
        std::cout << "상" << std::endl;
        jumpY = pos.y - jumpH;
        isOnGround = true;
    }

    //하
    if (    
            pos.y - radius <= block_pos.y + block_len/2 + colBuffer
        &&  pos.y - radius >= block_pos.y + block_len/2 - colBuffer
        &&  pos.x <= block_pos.x + block_len/2 + colBuffer
        &&  pos.x >= block_pos.x - block_len/2 - colBuffer
        ) {
        std::cout << "하" << std::endl;
        isOnGround = false;
    }


    //총합
    sf::FloatRect ball_F = ball.getGlobalBounds();
    sf::FloatRect block_F = block.getGlobalBounds();
    if (ball_F.intersects(block_F)) {
        
        ball.setPosition(pos.x - colBuffer/10*(block_pos.x-pos.x), pos.y- colBuffer/10*(block_pos.y-pos.y));
    } 

}

void Ball::applyGravity() {
    sf::Vector2f pos = ball.getPosition();

    jumpS = (pos.y - jumpY) / jumpDelta + 0.1f;
    
    if (!isOnGround) {
        ball.setPosition(pos.x, pos.y + jumpS);
    } else if (pos.y > jumpY) {
        ball.setPosition(pos.x, pos.y - jumpS);
    } else {
        isOnGround = false;
    }

    if (pos.y > 500.f) {
        jumpY = pos.y - jumpH;
        isOnGround = true;
    }

   

    
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(ball);
}

sf::Vector2f Ball::getPosition() const {
    return ball.getPosition();
}
