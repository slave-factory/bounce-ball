#include "ball.hpp"

Ball::Ball(float r, float speed)
    : radius(r), moveSpeed(speed), isOnGround(false) {
    ball.setRadius(radius);
    ball.setOrigin(radius,radius);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOutlineThickness(1.f);
    ball.setOutlineColor(sf::Color::Black);
    ball.setPosition(setOriginX, setOriginY);  // 초기 위치
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


void Ball::collide(const sf::RectangleShape& block) {
    sf::Vector2f pos = ball.getPosition();
    sf::Vector2f block_pos = block.getPosition();
   
    
    // 하
    if (    
            pos.y - radius <= block_pos.y + blockLen/2 + colBuffer
        &&  pos.y - radius >= block_pos.y + blockLen/2 - colBuffer
        &&  pos.x <= block_pos.x + blockLen/2 + colBuffer
        &&  pos.x >= block_pos.x - blockLen/2 - colBuffer
        ) {
        isOnGround = false;
        return;
        
    }

    // 총합
    sf::FloatRect ball_F = ball.getGlobalBounds();
    sf::FloatRect block_F = block.getGlobalBounds();
    if (ball_F.intersects(block_F)) {
        isOnGround = false;
        ball.setPosition(pos.x - colBuffer/10*(block_pos.x-pos.x), pos.y- colBuffer/50*(block_pos.y-pos.y));
        return;
    } 

     // 상
    if (    
            pos.y + radius >= block_pos.y - blockLen/2 - colBuffer
        &&  pos.y + radius <= block_pos.y - blockLen/2 + colBuffer*2
        &&  pos.x <= block_pos.x + blockLen/2 + colBuffer*2.5
        &&  pos.x >= block_pos.x - blockLen/2 - colBuffer*2.5
        ) {
            
        jumpY = pos.y - jumpH;
        isOnGround = true;
        return;
    }


}

bool Ball::oneCollide(sf::RectangleShape& block) {
    sf::Vector2f pos = ball.getPosition();
    sf::Vector2f block_pos = block.getPosition();

    // 하
    if (    
            pos.y - radius <= block_pos.y + blockLen/2 + colBuffer &&
            pos.y - radius >= block_pos.y + blockLen/2 - colBuffer &&
            pos.x <= block_pos.x + blockLen/2 + colBuffer &&
            pos.x >= block_pos.x - blockLen/2 - colBuffer
        ) {
        isOnGround = false;
        return false;  
    }

    // 총합
    sf::FloatRect ball_F = ball.getGlobalBounds();
    sf::FloatRect block_F = block.getGlobalBounds();
    if (ball_F.intersects(block_F)) {
        isOnGround = false;
        ball.setPosition(
            pos.x - colBuffer / 10 * (block_pos.x - pos.x),
            pos.y - colBuffer / 50 * (block_pos.y - pos.y)
        );
        return false;  
    } 

    // 상
    if (    
            pos.y + radius >= block_pos.y - blockLen/2 - colBuffer &&
            pos.y + radius <= block_pos.y - blockLen/2 + colBuffer*2 &&
            pos.x <= block_pos.x + blockLen/2 + colBuffer*2.5 &&
            pos.x >= block_pos.x - blockLen/2 - colBuffer*2.5
        ) {
        jumpY = pos.y - jumpH - 10.f;
        isOnGround = true;
        return true;  
    }

    return false;  // 충돌 없음
}

bool Ball::starCollide(sf::ConvexShape& block) {
    sf::Vector2f pos = ball.getPosition();
    sf::Vector2f block_pos = block.getPosition();

   
    // 총합
    sf::FloatRect ball_F = ball.getGlobalBounds();
    sf::FloatRect block_F = block.getGlobalBounds();
    if (ball_F.intersects(block_F)) {
        return true;  
    } 

    

    return false;  // 충돌 없음
}

void Ball::jumpCollide(const sf::RectangleShape& block) {
    sf::Vector2f pos = ball.getPosition();
    sf::Vector2f block_pos = block.getPosition();
   
    
    // 하
    if (    
            pos.y - radius <= block_pos.y + blockLen/2 + colBuffer
        &&  pos.y - radius >= block_pos.y + blockLen/2 - colBuffer
        &&  pos.x <= block_pos.x + blockLen/2 + colBuffer
        &&  pos.x >= block_pos.x - blockLen/2 - colBuffer
        ) {
        isOnGround = false;
        return;
        
    }

    // 총합
    sf::FloatRect ball_F = ball.getGlobalBounds();
    sf::FloatRect block_F = block.getGlobalBounds();
    if (ball_F.intersects(block_F)) {
        isOnGround = false;
        ball.setPosition(pos.x - colBuffer/10*(block_pos.x-pos.x), pos.y- colBuffer/50*(block_pos.y-pos.y));
        return;
    } 

     // 상
    if (    
            pos.y + radius >= block_pos.y - blockLen/2 - colBuffer
        &&  pos.y + radius <= block_pos.y - blockLen/2 + colBuffer*2
        &&  pos.x <= block_pos.x + blockLen/2 + colBuffer*2.5
        &&  pos.x >= block_pos.x - blockLen/2 - colBuffer*2.5
        ) {
            
        jumpY = pos.y - jumpH - 100.f;
        isOnGround = true;
        return;
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

    if (pos.y > 600.f) {
        // ball.setPosition(setOriginX,setOriginY);
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
